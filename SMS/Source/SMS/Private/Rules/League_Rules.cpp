
#include "Rules/League_Rules.h"
#include "Data/TeamData/TeamMatchData.h"
#include "Gamemodes/SMS_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/RaceLineupManager.h"
#include "Managers/RacerCareerManager.h"
#include "Managers/TeamManager.h"
#include "Managers/RaceManagers/RaceManager_Base.h"
#include "UI/League/Program/League_RacerStatsLine.h"


void ULeague_Rules::SetupMatch()
{
	BindDelegates();
	InitializeRules();
}


void ULeague_Rules::InitializeRules()
{
	TeamPositions.Add(EPositionTypes::Senior);
	TeamPositions.Add(EPositionTypes::Senior);
	TeamPositions.Add(EPositionTypes::Senior);
	TeamPositions.Add(EPositionTypes::Senior);
	TeamPositions.Add(EPositionTypes::Junior);
	TeamPositions.Add(EPositionTypes::Replacement);
	TeamPositions.Add(EPositionTypes::Senior);
	TeamPositions.Add(EPositionTypes::Senior);
	TeamPositions.Add(EPositionTypes::Senior);
	TeamPositions.Add(EPositionTypes::Senior);
	TeamPositions.Add(EPositionTypes::Junior);
	TeamPositions.Add(EPositionTypes::Replacement);
	ReplacementRules.Emplace(2, EPositionTypes::Junior);
	ReplacementRules.Emplace(1, EPositionTypes::Senior);
	ReplacementRules.Emplace(5, EPositionTypes::Replacement);
	TrackCleaningRaces.Add(4);
	TrackCleaningRaces.Add(7);
	TrackCleaningRaces.Add(10);
	TrackCleaningRaces.Add(13);
}

void ULeague_Rules::HandleRaceFinished()
{
	Super::HandleRaceFinished();
	if (CurrentRace <= Races.Num())
	{
		Races[CurrentRace].RaceManager->OnChangedRaceStatusDelegate.Broadcast(true);
		bool IsNominatedRace = Races[CurrentRace].RaceManager->IsNominatedRace();
		Races[CurrentRace].RaceLineupManager->OnHandleRaceLinesRequestDelegate.Broadcast(IsNominatedRace);
	}
	else OnRacingFinishedDelegate.Broadcast();
}


void ULeague_Rules::SetTeam(ETeams NewTeam, bool IsVisitor)
{
	if (ASMS_GameMode* CurrentGameMode = Cast<ASMS_GameMode>(UGameplayStatics::GetGameMode(this)))
	{
		FTeamMatchData Data;
		for (const auto& Racer : CurrentGameMode->GetTeamData(NewTeam).Racers)
		{
			if (URacerMatchManager* RacerMatchManager = NewObject<URacerMatchManager>(this))
			{
				Data.Racers.Add(RacerMatchManager);
				RacerMatchManager->Initialize(Racer->GetRacerData());
			}
		}
		Data.Team = CurrentGameMode->GetTeamData(NewTeam).Team;
		Data.TrackData = CurrentGameMode->GetTeamData(NewTeam).TrackData;
		Data.IsVisitorTeam = IsVisitor;
		if (!IsVisitor) CreateTrackManager(Data.TrackData);
		InitializeTeam(Data, Data.IsVisitorTeam ? VisitorTeamManager : HomeTeamManager);
	}
}


void ULeague_Rules::InitializeTeam(const FTeamMatchData& TeamData, TObjectPtr<UTeamManager>& OutManager)
{
	OutManager = NewObject<UTeamManager>(this);
	OutManager->InitializeManager();
	OutManager->SetTeamData(TeamData);
}


void ULeague_Rules::PopulateRacers()
{
	OnScoreUpdatedDelegate.AddUObject(this, &ULeague_Rules::UpdateScore);
	TArray<TObjectPtr<UTeamManager>> TeamManagers;
	TeamManagers.Add(HomeTeamManager);
	TeamManagers.Add(VisitorTeamManager);
	if (TeamManagers.IsEmpty()) return;
	for (const auto& Manager : TeamManagers)
	{
		Manager->ForEachRacerInLineup([this, Manager](int RacerNumber)
		{
			for (const auto& RacerStatsLine : Manager->GetRacerStatsLines())
			{
				if (RacerStatsLine->GetID() == RacerNumber)
				{
					if (TObjectPtr<URacerMatchManager>* FoundManager = Manager->GetRacers().Find(RacerNumber))
					{
						RacerStatsLine->InitializeManagers(*FoundManager);
						break;
					}
				}
			}
		});
		Manager->ForEachRacerInLineup(TFunction<void(const TObjectPtr<URacerMatchManager>&)>([this](URacerMatchManager* RacerManagerRef)
		{
			RequestToAssignRacersToRace(RacerManagerRef);
		}));
	}
}


void ULeague_Rules::PrepareToEndMatch()
{
	CollectTeamsStatistics();
	CollectRacerStatistics();
}


void ULeague_Rules::CollectRacerStatistics()
{
	for (const auto& Racer : HomeTeamManager->GetRacerManagers())
	{
		Racer->CollectMatchStatistics();
	}
	for (const auto& Racer : VisitorTeamManager->GetRacerManagers())
	{
		Racer->CollectMatchStatistics();
	}
}


void ULeague_Rules::CollectTeamsStatistics()
{
	if (!VisitorTeamManager || !HomeTeamManager) return;
	TMap<ETeams, int32> VisitorTeamData;
	TMap<ETeams, int32> HomeTeamData;
	
	int32 HomeTeamScore = HomeTeamManager->GetTeamScore();
	int32 VisitorTeamScore = VisitorTeamManager->GetTeamScore();

	VisitorTeamData.Add(VisitorTeamManager->GetTeam(), VisitorTeamScore);
	HomeTeamData.Add(HomeTeamManager->GetTeam(), HomeTeamScore);
	
	if (HomeTeamScore > VisitorTeamScore)
	{
		HomeTeamManager->CollectTeamStatistics(EMatchResults::Win, VisitorTeamData);
		VisitorTeamManager->CollectTeamStatistics(EMatchResults::Loss, HomeTeamData);
		return;
	}
	if (HomeTeamScore < VisitorTeamScore)
	{
		HomeTeamManager->CollectTeamStatistics(EMatchResults::Loss, VisitorTeamData);
		VisitorTeamManager->CollectTeamStatistics(EMatchResults::Win,  HomeTeamData);
		return;
	}
	HomeTeamManager->CollectTeamStatistics(EMatchResults::Draw, VisitorTeamData);
	VisitorTeamManager->CollectTeamStatistics(EMatchResults::Draw, HomeTeamData);
}


void ULeague_Rules::HandleMatchClosed()
{
	HomeTeamManager = nullptr;
	VisitorTeamManager = nullptr;
	OnScoreUpdatedDelegate.Clear();
	Super::HandleMatchClosed();
}


bool ULeague_Rules::CanStartMatch() const
{
	if (!HomeTeamManager || !VisitorTeamManager) return false;
	if (!HomeTeamManager->IsRosterValid()) return false;
	if (!VisitorTeamManager->IsRosterValid()) return false;
	HomeTeamManager->LockChosenRacers();
	VisitorTeamManager->LockChosenRacers();
	return true;
}


void ULeague_Rules::MakeRandomRosters()
{
	HomeTeamManager->MakeRandomTeamRoster();
	VisitorTeamManager->MakeRandomTeamRoster();
}


void ULeague_Rules::UpdateScore(bool IsVisitor, int32 PointsToAdd, int32 RaceID)
{
	IsVisitor ? VisitorTeamManager->UpdateScore(PointsToAdd, RaceID) : HomeTeamManager->UpdateScore(PointsToAdd, RaceID);
}

bool ULeague_Rules::CheckPossibleAmountOfReplacements(int32 AmountOfReplacements, EPositionTypes Position) const
{
	for (const auto& Rule : ReplacementRules)
	{
		if (Rule.PositionType == Position) return Rule.MaxReplacements > AmountOfReplacements;
	}
	return false;
}


bool ULeague_Rules::IsRacerEligible(int32 RaceLineID, int32 Age) const
{
	if (TeamPositions[RaceLineID - 1] == EPositionTypes::Junior) return IsJunior(Age);
	return true;
}


bool ULeague_Rules::CanReplace(const URacerMatchManager* OriginalRacer, const URacerMatchManager* ReplacementRacer, int32 OwnTeamScore, int32 EnemyTeamScore) const
{
	if (!OriginalRacer || !ReplacementRacer) return false;
	if (OriginalRacer == ReplacementRacer) return false;
	if (!ReplacementRacer->CanDriveMore(MaxAmountOfRaces)) return false;
	if (!CheckPossibleAmountOfReplacements(ReplacementRacer->GetAmountOfReplacements(), GetPositionType(ReplacementRacer->GetRacerNumber()))) return false;
	
	int32 originalRacerNumber = OriginalRacer->GetRacerNumber();
	int32 replaceRacerNumber = ReplacementRacer->GetRacerNumber();
	if (GetPositionType(originalRacerNumber) == EPositionTypes::Replacement) return false;
	if (IsTeamLosing(OwnTeamScore, EnemyTeamScore))
	{
		if (GetPositionType(originalRacerNumber) == EPositionTypes::Junior)
			return GetPositionType(replaceRacerNumber) == EPositionTypes::Replacement && IsJunior(ReplacementRacer->GetRacerAge());
		return true;
	}
	else
	{
		if (GetPositionType(originalRacerNumber) != EPositionTypes::Junior)
		{
			return GetPositionType(replaceRacerNumber) == EPositionTypes::Junior || GetPositionType(replaceRacerNumber) == EPositionTypes::Replacement;
		}
		if (GetPositionType(originalRacerNumber) == EPositionTypes::Junior)
		{
			if (GetPositionType(replaceRacerNumber) == EPositionTypes::Replacement)
			{
				return IsJunior(ReplacementRacer->GetRacerAge());
			}
			if (GetPositionType(replaceRacerNumber) != EPositionTypes::Junior) return false;
		}
	}
	return false;
}


bool ULeague_Rules::CanParticipateInNominatedRace(const URacerMatchManager* RacerManagerRef) const
{
	return !RacerManagerRef->DidParticipateInNominatedRace() && RacerManagerRef->CanDriveMore(MaxAmountOfRaces);
}


bool ULeague_Rules::IsTeamLosing(int32 OwnTeamScore, int32 EnemyTeamScore) const
{
	return EnemyTeamScore >= OwnTeamScore + TeamScoreDifference;
}


TObjectPtr<UTeamManager> ULeague_Rules::GetTeamManager(bool IsVisitor) const
{
	return IsVisitor ? VisitorTeamManager : HomeTeamManager;
}

int32 ULeague_Rules::GetTeamScore(bool IsVisitor) const
{
	return IsVisitor ? VisitorTeamManager->GetTeamScore() : HomeTeamManager->GetTeamScore();
}

int32 ULeague_Rules::GetTeamRaceScore(bool IsVisitor, int32 RaceID) const
{
	return IsVisitor ? VisitorTeamManager->GetRaceScore(RaceID) : HomeTeamManager->GetRaceScore(RaceID);
}
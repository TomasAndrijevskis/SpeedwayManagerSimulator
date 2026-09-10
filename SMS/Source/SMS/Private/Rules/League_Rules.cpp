
#include "Rules/League_Rules.h"
#include "Data/TeamData/TeamMatchData.h"
#include "Gamemodes/SMS_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/RacerCareerManager.h"
#include "Managers/TeamManager.h"
#include "Subsystems/RulesSubsystem.h"
#include "UI/League/Program/League_RacerStatsLine.h"


void ULeague_Rules::SetupMatch()
{
	BindDelegates();
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


void ULeague_Rules::CollectTeamsStatistics()
{
	if (URulesSubsystem* Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<URulesSubsystem>())
	{
		Subsystem->DecideMatchWinner(HomeTeamManager, VisitorTeamManager);
	}
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


void ULeague_Rules::PrepareToEndMatch()
{
	CollectTeamsStatistics();
	CollectRacerStatistics();
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
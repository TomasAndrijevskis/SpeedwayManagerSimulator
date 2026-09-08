
#include "Rules/LeagueRules.h"
#include "Data/TeamData/TeamMatchData.h"
#include "Gamemodes/SMS_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/RacerCareerManager.h"
#include "Managers/TeamManager.h"
#include "Subsystems/RulesSubsystem.h"
#include "UI/League/Program/League_RacerStatsLine.h"


void ULeagueRules::SetupMatch()
{
	BindDelegates();
}


void ULeagueRules::SetTeam(ETeams NewTeam, bool IsVisitor)
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


void ULeagueRules::InitializeTeam(const FTeamMatchData& TeamData, TObjectPtr<UTeamManager>& OutManager)
{
	OutManager = NewObject<UTeamManager>(this);
	OutManager->InitializeManager();
	OutManager->SetTeamData(TeamData);
}


void ULeagueRules::PopulateRacers()
{
	OnScoreUpdatedDelegate.AddUObject(this, &ULeagueRules::UpdateScore);
	TArray<TObjectPtr<UTeamManager>> TeamManagers;
	TeamManagers.Add(HomeTeamManager);
	TeamManagers.Add(VisitorTeamManager);
	if (TeamManagers.IsEmpty()) return;
	//UE_LOG(LogTemp, Log, TEXT("TeamManagers not null"));
	for (const auto& Manager : TeamManagers)
	{
		Manager->ForEachRacerInLineup([this, Manager](int RacerNumber)
		{
			//UE_LOG(LogTemp, Error, TEXT("RacerNumber %i"), RacerNumber);
			for (const auto& RacerStatsLine : Manager->GetRacerStatsLines())
			{
				if (RacerStatsLine->GetID() == RacerNumber)
				{
					//UE_LOG(LogTemp, Error, TEXT("=========="));
					//UE_LOG(LogTemp, Error, TEXT("stats line id %i"), RacerStatsLine->GetID());
					
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


void ULeagueRules::CollectTeamsStatistics()
{
	if (URulesSubsystem* Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<URulesSubsystem>())
	{
		Subsystem->DecideMatchWinner(HomeTeamManager, VisitorTeamManager);
	}
}


void ULeagueRules::CollectRacerStatistics()
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


void ULeagueRules::EndMatch()
{
	CollectTeamsStatistics();
	CollectRacerStatistics();
	ClearDependencies();
}


void ULeagueRules::ClearDependencies()
{
	Super::ClearDependencies();
	HomeTeamManager = nullptr;
	VisitorTeamManager = nullptr;
	OnScoreUpdatedDelegate.Clear();
}


bool ULeagueRules::CanStartMatch() const
{
	if (!HomeTeamManager || !VisitorTeamManager) return false;
	if (!HomeTeamManager->IsRosterValid()) return false;
	if (!VisitorTeamManager->IsRosterValid()) return false;
	HomeTeamManager->LockChosenRacers();
	VisitorTeamManager->LockChosenRacers();
	return true;
}


void ULeagueRules::MakeRandomRosters()
{
	HomeTeamManager->MakeRandomTeamRoster();
	VisitorTeamManager->MakeRandomTeamRoster();
}


void ULeagueRules::UpdateScore(bool IsVisitor, int32 PointsToAdd, int32 RaceID)
{
	IsVisitor ? VisitorTeamManager->UpdateScore(PointsToAdd, RaceID) : HomeTeamManager->UpdateScore(PointsToAdd, RaceID);
}


TObjectPtr<UTeamManager> ULeagueRules::GetTeamManager(bool IsVisitor) const
{
	return IsVisitor ? VisitorTeamManager : HomeTeamManager;
}

int32 ULeagueRules::GetTeamScore(bool IsVisitor) const
{
	return IsVisitor ? VisitorTeamManager->GetTeamScore() : HomeTeamManager->GetTeamScore();
}

int32 ULeagueRules::GetTeamRaceScore(bool IsVisitor, int32 RaceID) const
{
	return IsVisitor ? VisitorTeamManager->GetRaceScore(RaceID) : HomeTeamManager->GetRaceScore(RaceID);
}
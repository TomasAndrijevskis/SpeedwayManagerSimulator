
#include "Rules/LeagueRules.h"
#include "Data/TeamData/TeamMatchData.h"
#include "Gamemodes/SMS_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/RaceManager.h"
#include "Managers/ScoreManager.h"
#include "Managers/TeamManager.h"
#include "UI/League/Program/League_RacerStatsLine.h"


void ULeagueRules::SetupMatch()
{
	ScoreManager = NewObject<UScoreManager>(this);
	BindDelegates();
}


void ULeagueRules::SetTeam(ETeams NewTeam, bool IsVisitor)
{
	ASMS_GameMode* CurrentGameMode = Cast<ASMS_GameMode>(UGameplayStatics::GetGameMode(this));
	if (CurrentGameMode)
	{
		FTeamMatchData Data = CurrentGameMode->GetTeamData(NewTeam);
		Data.IsVisitorTeam = IsVisitor;
		if (!IsVisitor) CreateTrackManager(Data.TrackData);
		Teams.Add(Data);
	}
}


void ULeagueRules::CreateRacerManagers(TArray<UTeamManager*> TeamManagersRef)
{
	if (TeamManagersRef.IsEmpty()) return;
	for (const auto& Manager : TeamManagersRef)
	{
		Manager->CreateRacerManagers();
	}
	PopulateRacers(TeamManagersRef);
	OnRacerManagersCreatedDelegate.Broadcast(TeamManagersRef);
}


FTeamMatchData* ULeagueRules::GetTeamData(bool Status)
{
	for (auto& Team : Teams)
	{
		if (Team.IsVisitorTeam == Status) return &Team;
	}
	return nullptr;
}


void ULeagueRules::PopulateRacers(TArray<UTeamManager*> TeamManagersRef)
{
	if (TeamManagersRef.IsEmpty()) return;
	for (const auto& Manager : TeamManagersRef)
	{
		Manager->ForEachRacerInLineup([this, Manager](int RacerNumber)
		{
			for (const auto& RacerStatsLine : Manager->GetRacerStatsLines())
			{
				if (RacerStatsLine->GetID() == RacerNumber)
				{
					if (URacerManager** FoundManager = Manager->GetRacerManagers().Find(RacerNumber))
					{
						RacerStatsLine->InitializeManagers(*FoundManager);
						break;
					}
				}
			}
		});
		Manager->ForEachRacerInLineup([this](URacerManager* RacerManagerRef)
		{
			RequestToAssignRacersToRace(RacerManagerRef);
		});
	}
}

void ULeagueRules::HandleRaceFinished()
{
	if (ScoreManager) ScoreManager->ClearLastRaceScore();
	Super::HandleRaceFinished();
}


void ULeagueRules::BindRaceDelegates()
{
	if (!Races[CurrentRace].RaceManager) return;
	Races[CurrentRace].RaceManager->OnRaceScoreUpdatedDelegate.AddUObject(ScoreManager, &UScoreManager::UpdateScore);
}


UScoreManager* ULeagueRules::GetScoreManager() const {return ScoreManager;}
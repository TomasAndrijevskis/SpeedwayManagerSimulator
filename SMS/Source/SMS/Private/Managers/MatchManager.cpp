
#include "Managers/MatchManager.h"
#include "Gamemodes/SMS_GameMode.h"
#include "Managers/RaceManager.h"
#include "Managers/ScoreManager.h"
#include "Managers/TeamManager.h"
#include "UI/League/Program/RacerStatsLine.h"


void UMatchManager::InitializeManager(ASMS_GameMode* CurrentGameMode)
{
	if (!CurrentGameMode) return;
	GameMode = CurrentGameMode;
	ScoreManager = GameMode->GetScoreManager();
	if (!ScoreManager) return;
	BindDelegates();
}


void UMatchManager::BindDelegates()
{
	OnRaceStaredDelegate.AddUObject(this, &UMatchManager::SimulateRace);
}


void UMatchManager::SimulateRace()
{
	if (CurrentRace <= RaceManagers.Num()-1)
	{
		BindRaceDelegates();
		RaceManagers[CurrentRace]->OnSimulateRaceRequestDelegate.Broadcast();
		HandleRaceFinished();
	}
}


void UMatchManager::BindRaceDelegates()
{
	RaceManagers[CurrentRace]->OnRaceScoreUpdatedDelegate.AddUObject(ScoreManager, &UScoreManager::UpdateScore);
}


void UMatchManager::HandleRaceFinished()
{
	ScoreManager->ClearLastRaceScore();
	CurrentRace++;
	if (CurrentRace <= RaceManagers.Num()-1) RaceManagers[CurrentRace]->OnRaceStatusChangedDelegate.Broadcast(true);
	else OnMatchEndedDelegate.Broadcast();
}


void UMatchManager::CreateRacerManagers(TArray<UTeamManager*> TeamManagersRef)
{
	if (TeamManagersRef.IsEmpty()) return;
	for (const auto& Manager : TeamManagersRef)
	{
		Manager->CreateRacerManagers();
	}
	PopulateRacers(TeamManagersRef);
	OnRacerManagersCreatedDelegate.Broadcast(TeamManagersRef);
}


void UMatchManager::PopulateRacers(TArray<UTeamManager*> TeamManagersRef)
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
		Manager->ForEachRacerInLineup([this](const FRacerMatchData& Data, URacerManager* RacerManagerRef)
		{
			RequestToAssignRacersToRace(Data, RacerManagerRef);
		});
	}
}


void UMatchManager::AddNewRace(URaceManager* NewRace)
{
	if (!NewRace) return;
	RaceManagers.Add(NewRace);
}


void UMatchManager::RequestToAssignRacersToRace(const FRacerMatchData& Data, URacerManager* RacerManagerRef)
{
	for (const auto& RaceManager : RaceManagers)
	{
		RaceManager->AssignRacerToRace(Data, RacerManagerRef);
	}
}


void UMatchManager::SetTeamID(int NewTeamID, bool IsVisitor)
{
	FTeamMatchData Data = GameMode->GetTeamData(NewTeamID);
	Data.IsVisitorTeam = IsVisitor;
	Teams.Add(Data);
}


FTeamMatchData* UMatchManager::GetTeamData(bool Status)
{
	for (auto& Team : Teams)
	{
		if (Team.IsVisitorTeam == Status) return &Team;
	}
	return nullptr;
}


int UMatchManager::GetCurrentRaceNumber() const {return CurrentRace;}
int UMatchManager::GetAmountOfRaces() const{return RaceManagers.Num();}
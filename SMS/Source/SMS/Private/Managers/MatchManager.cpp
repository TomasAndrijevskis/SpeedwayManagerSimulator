
#include "Managers/MatchManager.h"
#include "Gamemodes/SMS_GameMode.h"
#include "Managers/RaceManager.h"
#include "Managers/ScoreManager.h"
#include "UI/League/Program/RacerStatsLine.h"
#include "UI/League/Program/TeamRoster.h"


void UMatchManager::InitializeManager(ASMS_GameMode* CurrentGameMode)
{
	if (!CurrentGameMode) return;
	GameMode = CurrentGameMode;
	ScoreManager = GameMode->ScoreManager;
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
		RaceManagers[CurrentRace]->OnRaceSimulationStartedDelegate.Broadcast();
		HandleRaceFinished();
	}
}


void UMatchManager::BindRaceDelegates()
{
	RaceManagers[CurrentRace]->OnRaceScoreUpdatedDelegate.AddUObject(ScoreManager, &UScoreManager::UpdateOverallScore);
	ScoreManager->OnOverallScoreUpdatedDelegate.AddUObject(RaceManagers[CurrentRace], &URaceManager::UpdateOverallScore);
}


void UMatchManager::HandleRaceFinished()
{
	RaceManagers[CurrentRace]->OnRaceStatusChangedDelegate.Broadcast(false);
	RaceManagers[CurrentRace]->OnRaceScoreUpdatedDelegate.Clear();
	ScoreManager->OnOverallScoreUpdatedDelegate.Clear();
	CurrentRace++;
	if (CurrentRace <= RaceManagers.Num()-1) RaceManagers[CurrentRace]->OnRaceStatusChangedDelegate.Broadcast(true);
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


void UMatchManager::SetTeamsID(int NewHomeTeamID, int NewVisitorTeamID)
{
	HomeTeamID = NewHomeTeamID;
	VisitorTeamID = NewVisitorTeamID;
}


int UMatchManager::GetCurrentRaceNumber() const {return CurrentRace;}
int UMatchManager::GetHomeTeamID() const{return HomeTeamID;}
int UMatchManager::GetVisitorTeamID() const{return VisitorTeamID;}
int UMatchManager::GetAmountOfRaces() const{return RaceManagers.Num();}
FTeamRosterData* UMatchManager::GetVisitorTeamData() const{return GameMode->GetTeamData(VisitorTeamID);}
FTeamRosterData* UMatchManager::GetHomeTeamData()const{return GameMode->GetTeamData(HomeTeamID);}
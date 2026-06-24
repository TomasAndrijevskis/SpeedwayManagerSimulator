
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
	OnPopulateRacersRequestDelegate.AddUObject(this, &UMatchManager::PopulateRacers);
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
	if (CurrentRace == 13) OnNominatedRacesStaredDelegate.Broadcast(true);
}


void UMatchManager::PopulateRacers(TArray<UTeamRoster*> TeamRosters)
{
	if (TeamRosters.IsEmpty()) return;
	for (const auto& Roster : TeamRosters)
	{
		Roster->TeamManager->CreateRacerManagers();
		Roster->TeamManager->ForEachRacerInLineup([this, Roster](int ID, const FRacerData& Data)
		{
			for (auto RacerStatsLine : Roster->GetRacerStatsLines())
			{
				if (RacerStatsLine->GetID() == ID)
				{
					RacerStatsLine->InitializeManagers(Data.RacerManager);
					break;
				}
			}
		});
		Roster->TeamManager->ForEachRacerInLineup([this](int ID, const FRacerData& Data)
		{
			RequestToAssignRacersToRace(Data, ID);
		});
	}
}



void UMatchManager::AddNewRace(URaceManager* NewRace)
{
	if (!NewRace) return;
	RaceManagers.Add(NewRace);
}


void UMatchManager::RequestToAssignRacersToRace(const FRacerData& Data, int ID)
{
	for (const auto& RaceManager : RaceManagers)
	{
		RaceManager->AssignRacerToRace(Data, ID);
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
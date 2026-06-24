
#include "Managers/MatchManager.h"
#include "Gamemodes/SMS_GameMode.h"
#include "UI/League/Program/RacerStatsLine.h"
#include "UI/League/Program/TeamRoster.h"


void UMatchManager::Init(ASMS_GameMode* CurrentGameMode)
{
	if (!CurrentGameMode) return;
	GameMode = CurrentGameMode;
	BindDelegates();
}


void UMatchManager::BindDelegates()
{
	OnPopulateRacersRequestDelegate.AddUObject(this, &UMatchManager::PopulateRacers);
	OnRaceStaredDelegate.AddUObject(this, &UMatchManager::SimulateRace);
}


void UMatchManager::SimulateRace()
{
	if (CurrentRace <= Races.Num()-1)
	{
		BindRaceDelegates();
		Races[CurrentRace]->OnSimulateRaceRequestDelegate.Broadcast();
		HandleRaceFinished();
	}
}


void UMatchManager::BindRaceDelegates()
{
	Races[CurrentRace]->OnScoreUpdatedDelegate.AddUObject(this, &UMatchManager::UpdateOverallScore);
	OnOverallScoreUpdatedDelegate.AddUObject(Races[CurrentRace], &URace::UpdateOverallScore);
}


void UMatchManager::HandleRaceFinished()
{
	Races[CurrentRace]->OnRaceStatusChangedDelegate.Broadcast(false);
	Races[CurrentRace]->OnScoreUpdatedDelegate.Clear();
	OnOverallScoreUpdatedDelegate.Clear();
	CurrentRace++;
	if (CurrentRace <= Races.Num()-1) Races[CurrentRace]->OnRaceStatusChangedDelegate.Broadcast(true);
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


void UMatchManager::UpdateOverallScore(int AddHomePts, int AddVisitorPts)
{
	HomeOverallScore += AddHomePts;
	VisitorOverallScore += AddVisitorPts;
	OnOverallScoreUpdatedDelegate.Broadcast(HomeOverallScore, VisitorOverallScore);
}


void UMatchManager::AddNewRace(URace* NewRace)
{
	Races.Add(NewRace);
}


void UMatchManager::RequestToAssignRacersToRace(const FRacerData& Data, int ID)
{
	for (const auto& Race : Races)
	{
		Race->OnAssignRacerRequestDelegate.Broadcast(Data, ID);
	}
}


void UMatchManager::SetTeamsID(int NewHomeTeamID, int NewVisitorTeamID)
{
	HomeTeamID = NewHomeTeamID;
	VisitorTeamID = NewVisitorTeamID;
}


int UMatchManager::GetHomeTeamScore() const{return HomeOverallScore;}
int UMatchManager::GetVisitorTeamScore() const{return VisitorOverallScore;}
int UMatchManager::GetCurrentRaceNumber() const {return CurrentRace;}
int UMatchManager::GetHomeTeamID() const{return HomeTeamID;}
int UMatchManager::GetVisitorTeamID() const{return VisitorTeamID;}
int UMatchManager::GetAmountOfRaces() const{return Races.Num();}
FTeamRosterData* UMatchManager::GetVisitorTeamData() const{return GameMode->GetTeamData(VisitorTeamID);}
FTeamRosterData* UMatchManager::GetHomeTeamData()const{return GameMode->GetTeamData(HomeTeamID);}

#include "Managers/MatchManager.h"
#include "Gamemodes/SMS_GameMode.h"


void UMatchManager::Init(ASMS_GameMode* CurrentGameMode)
{
	GameMode = CurrentGameMode;
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


void UMatchManager::AssignRacersToRace(const FString& Name, int Id)
{
	for (const auto& Race : Races)
	{
		Race->OnAssignRacerRequestDelegate.Broadcast(Name, Id);
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
FTeamRosterData* UMatchManager::GetVisitorTeamData() const{return GameMode->GetTeamData(VisitorTeamID);}
FTeamRosterData* UMatchManager::GetHomeTeamData()const{return GameMode->GetTeamData(HomeTeamID);}
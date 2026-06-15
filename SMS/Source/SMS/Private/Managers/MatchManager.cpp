
#include "Managers/MatchManager.h"
#include "Gamemodes/SMS_GameMode.h"


void UMatchManager::Init(ASMS_GameMode* CurrentGameMode)
{
	GameMode = CurrentGameMode;
	//if (!GameMode) return;
}

void UMatchManager::SimulateRace()
{
	UE_LOG(LogTemp, Warning, TEXT("Simulate race"));
	if (CurrentRace <= Races.Num()-1)
	{
		UE_LOG(LogTemp, Warning, TEXT("CurrentRace: %i"), CurrentRace+1);
		Races[CurrentRace]->OnScoreUpdatedDelegate.AddUObject(this, &UMatchManager::UpdateOverallScore);
		Races[CurrentRace]->OnSimulateRaceRequestDelegate.Broadcast();
		Races[CurrentRace]->OnRaceStatusChangedDelegate.Broadcast(false);
		Races[CurrentRace]->OnScoreUpdatedDelegate.Clear();
		CurrentRace++;
		if (CurrentRace <= Races.Num()-1) Races[CurrentRace]->OnRaceStatusChangedDelegate.Broadcast(true);
		/*
		   Races[CurrentRace]->OnOverallScoreUpdatedDelegate.AddUObject(this, &ULeagueProgram::SetOverallPts);
		   Races[CurrentRace]->OnRaceFinishedDelegate.AddUObject(this, &ULeagueProgram::OnRaceFinished);
		   Races[CurrentRace]->SimulateRace();
		   Races[CurrentRace]->OnOverallScoreUpdatedDelegate.Clear();
		   CurrentRace++;
		   if (CurrentRace < Races.Num()) Races[CurrentRace]->ChangeRaceStatus(true);
	   }*/
	}
}


void UMatchManager::UpdateOverallScore(int AddHomePts, int AddVisitorPts)
{
	HomeOverallScore += AddHomePts;
	VisitorOverallScore += AddVisitorPts;
	OnScoreUpdatedDelegate.Broadcast(HomeOverallScore, VisitorOverallScore);
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
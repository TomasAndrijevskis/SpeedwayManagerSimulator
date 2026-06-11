
#include "Managers/MatchManager.h"
#include "Gamemodes/SMS_GameMode.h"


void UMatchManager::SimulateRace()
{
	if (CurrentRace < AmountOfRaces)
	{
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


void UMatchManager::Init(ASMS_GameMode* CurrentGameMode)
{
	GameMode = CurrentGameMode;
	if (!GameMode) return;
	OnScoreUpdatedDelegate.AddUObject(this, &UMatchManager::UpdateScore);
}


void UMatchManager::SetTeamsID(int NewHomeTeamID, int NewVisitorTeamID)
{
	HomeTeamID = NewHomeTeamID;
	VisitorTeamID = NewVisitorTeamID;
}


void UMatchManager::SetOverallPts(int AddHomePts, int AddVisitorPts)
{
	HomeTeamScore += AddHomePts;
	VisitorTeamScore += AddVisitorPts;
	OnScoreUpdatedDelegate.Broadcast(HomeTeamScore, VisitorTeamScore);
}


void UMatchManager::SetAmountOfRaces(int NewAmount){AmountOfRaces = NewAmount;}
void UMatchManager::UpdateScore(int NewHomeTeamScore, int NewVisitorTeamScore){HomeTeamScore = NewHomeTeamScore;VisitorTeamScore = NewVisitorTeamScore;}
int UMatchManager::GetHomeTeamScore() const{return HomeTeamScore;}
int UMatchManager::GetVisitorTeamScore() const{return VisitorTeamScore;}
int UMatchManager::GetCurrentRaceNumber() const {return CurrentRace;}
FTeamRosterData* UMatchManager::GetVisitorTeamData() const{return GameMode->GetTeamData(VisitorTeamID);}
FTeamRosterData* UMatchManager::GetHomeTeamData()const{return GameMode->GetTeamData(HomeTeamID);}
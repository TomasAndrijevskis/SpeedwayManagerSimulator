
#include "Gamemodes/Managers/MatchManager.h"
#include "Gamemodes/SMS_GameMode.h"


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


void UMatchManager::UpdateScore(int NewHomeTeamScore, int NewVisitorTeamScore){HomeTeamScore = NewHomeTeamScore;VisitorTeamScore = NewVisitorTeamScore;}
int UMatchManager::GetHomeTeamScore() const{return HomeTeamScore;}
int UMatchManager::GetVisitorTeamScore() const{return VisitorTeamScore;}
FTeamRosterData* UMatchManager::GetVisitorTeamData() const{return GameMode->GetTeamData(VisitorTeamID);}
FTeamRosterData* UMatchManager::GetHomeTeamData()const{return GameMode->GetTeamData(HomeTeamID);}
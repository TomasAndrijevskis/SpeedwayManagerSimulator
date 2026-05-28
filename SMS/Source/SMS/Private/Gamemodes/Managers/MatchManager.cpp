
#include "Gamemodes/Managers/MatchManager.h"


void UMatchManager::Init()
{
	OnMatchStartedDelegate.AddUObject(this, &UMatchManager::SetTeams);
	OnScoreUpdatedDelegate.AddUObject(this, &UMatchManager::UpdateScore);
}


void UMatchManager::SetTeams(FTeamRosterData* NewHomeTeam, FTeamRosterData* NewVisitorTeam){HomeTeamData = NewHomeTeam;VisitorTeamData = NewVisitorTeam;}
void UMatchManager::UpdateScore(int NewHomeTeamScore, int NewVisitorTeamScore){HomeTeamScore = NewHomeTeamScore;VisitorTeamScore = NewVisitorTeamScore;}
int UMatchManager::GetHomeTeamScore() const{return HomeTeamScore;}
int UMatchManager::GetVisitorTeamScore() const{return VisitorTeamScore;}
FTeamRosterData& UMatchManager::GetVisitorTeamData() const{return *VisitorTeamData;}
FTeamRosterData& UMatchManager::GetHomeTeamData()const{return *HomeTeamData;}
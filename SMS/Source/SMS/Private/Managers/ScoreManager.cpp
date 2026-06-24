
#include "Managers/ScoreManager.h"


void UScoreManager::UpdateOverallScore(int AddHomePts, int AddVisitorPts)
{
	HomeOverallScore += AddHomePts;
	VisitorOverallScore += AddVisitorPts;
	OnOverallScoreUpdatedDelegate.Broadcast(HomeOverallScore, VisitorOverallScore);
	OnHomePtsUpdatedDelegate.Broadcast(HomeOverallScore);
	OnVisitorPtsUpdatedDelegate.Broadcast(VisitorOverallScore);
}


int UScoreManager::GetHomeTeamScore() const{return HomeOverallScore;}
int UScoreManager::GetVisitorTeamScore() const{return VisitorOverallScore;}
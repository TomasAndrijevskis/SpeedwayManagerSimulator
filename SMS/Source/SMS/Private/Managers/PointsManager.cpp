
#include "Managers/PointsManager.h"


void UPointsManager::UpdateOverallScore(int HomeAddPoints, int VisitorAddPoints)
{
	HomeOverallPoints += HomeAddPoints;
	VisitorOverallPoints += VisitorAddPoints;
	OnScoreChangedDelegate.Broadcast(HomeOverallPoints, VisitorOverallPoints);
}
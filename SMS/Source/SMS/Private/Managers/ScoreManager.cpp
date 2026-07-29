
#include "Managers/ScoreManager.h"


void UScoreManager::AddTeamRef(FTeamMatchData* TeamData)
{
	Teams.Add(TeamData);
}


void UScoreManager::UpdateScore(int32 TeamID, int32 PointsToAdd)
{
	for (auto& Team : Teams)
	{
		if (Team->TeamID == TeamID)
		{
			Team->TeamScore += PointsToAdd;
			Team->LastRaceScore += PointsToAdd;
			OnTeamOverallScoreUpdatedDelegate.Broadcast(Team->TeamID, Team->TeamScore);
		}
	}
}


void UScoreManager::ClearLastRaceScore()
{
	for (auto& Team : Teams)
	{
		Team->LastRaceScore = 0;
	}
}


int32 UScoreManager::GetTeamScore(bool IsVisitor) const
{
	for (auto& Team : Teams)
	{
		if (Team->IsVisitorTeam == IsVisitor)
			return Team->TeamScore;
	}
	return 0;
}


int32 UScoreManager::GetRaceScore(bool IsVisitor) const
{
	for (auto& Team : Teams)
	{
		if (Team->IsVisitorTeam == IsVisitor)
			return Team->LastRaceScore;
	}
	return 0;
}

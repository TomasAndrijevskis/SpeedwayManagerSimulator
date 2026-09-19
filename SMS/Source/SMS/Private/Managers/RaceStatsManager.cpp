
#include "Managers/RaceStatsManager.h"
#include "UI/RaceStats/RaceLineStat.h"


void URaceStatsManager::HandleStatUpdate(const TArray<FRaceResultData>& RaceResultData)
{
	for (const auto& Data : RaceResultData)
	{
		OverallPoints += Data.Points;
	}
	for (const auto& Line : RaceLineStats)
	{
		for (const auto& Data : RaceResultData)
		{
			if (Line->GetID() == Data.RacerNumber)
			{
				Line->UpdateNumbers(Data.Points);
				Line->UpdateProgressBar(OverallPoints);
			}
		}
	}
}


void URaceStatsManager::AddRaceLineStat(URaceLineStat* NewRaceLineStat)
{
	RaceLineStats.Add(NewRaceLineStat);
}
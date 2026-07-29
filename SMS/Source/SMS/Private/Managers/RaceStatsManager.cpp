
#include "Managers/RaceStatsManager.h"
#include "UI/League/Program/Race/RaceStats/RaceLineStat.h"


void URaceStatsManager::HandleStatUpdate(const TArray<FRaceResultData>& RaceResultData)
{
	for (const auto& Data : RaceResultData)
	{
		OverallPoints += Data.RacerScore;
	}
	for (const auto& Line : RaceLineStats)
	{
		for (const auto& Data : RaceResultData)
		{
			if (Line->GetID() == Data.RaceLineID)
			{
				Line->UpdateNumbers(Data.RacerScore);
				Line->UpdateProgressBar(OverallPoints);
			}
		}
	}
}


void URaceStatsManager::AddRaceLineStat(URaceLineStat* NewRaceLineStat)
{
	RaceLineStats.Add(NewRaceLineStat);
}
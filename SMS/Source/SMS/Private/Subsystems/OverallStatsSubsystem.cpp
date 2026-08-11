
#include "Subsystems/OverallStatsSubsystem.h"


void UOverallStatsSubsystem::AddStat(const FRacerStatistics& CurrentMatchStatistics)
{
	for (auto& Stats : RacerStatistics)
	{
		if (Stats.RacerID == CurrentMatchStatistics.RacerID)
		{
			Stats.MatchStatistics.Append(CurrentMatchStatistics.MatchStatistics);
			return;
		}
	}
	RacerStatistics.Add(CurrentMatchStatistics);
}


TArray<FRacerStatistics>& UOverallStatsSubsystem::GetRacerStatistics(){return RacerStatistics;}
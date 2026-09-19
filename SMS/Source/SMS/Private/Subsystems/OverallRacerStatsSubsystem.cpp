
#include "Subsystems/OverallRacerStatsSubsystem.h"


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
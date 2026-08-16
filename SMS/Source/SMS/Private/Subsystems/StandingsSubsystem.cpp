
#include "Subsystems/StandingsSubsystem.h"

void UStandingsSubsystem::AddTeamStatistics(const FTeamStatistics& NewTeamStatistics)
{
	for (auto& Stats : TeamStatistics)
	{
		if (Stats.Team == NewTeamStatistics.Team)
		{
			Stats.MatchStatistics.Append(NewTeamStatistics.MatchStatistics);
			return;
		}
	}
	TeamStatistics.Add(NewTeamStatistics);
}


TArray<FTeamStatistics>& UStandingsSubsystem::GetTeamStatistics(){return TeamStatistics;}
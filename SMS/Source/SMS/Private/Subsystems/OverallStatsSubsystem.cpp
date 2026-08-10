
#include "Subsystems/OverallStatsSubsystem.h"


void UOverallStatsSubsystem::AddStat(const FRacerStatistics& CurrentMatchStatistics)
{
	for (auto& Stats : RacerStatistics)
	{
		if (Stats.RacerID == CurrentMatchStatistics.RacerID)
		{
			UE_LOG(LogTemp, Display, TEXT("Found %i"), Stats.RacerID);
			Stats.MatchStatistics.Append(CurrentMatchStatistics.MatchStatistics);
			return;
		}
	}
	RacerStatistics.Add(CurrentMatchStatistics);
}


void UOverallStatsSubsystem::PrintAllStats()
{
	for (const auto& Stats : RacerStatistics)
	{
		UE_LOG(LogTemp, Warning, TEXT("========"));
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Stats.RacerName);
		UE_LOG(LogTemp, Warning, TEXT("amount of matches %i"), Stats.MatchStatistics.Num());
		float points = 0;
		int32 races = 0;
		for (const auto& Element : Stats.MatchStatistics)
		{
			UE_LOG(LogTemp, Error, TEXT("Status: %hs"), Element.bIsVisitor ? "Visitor": "Home");
			UE_LOG(LogTemp, Error, TEXT("Bonuses %i"), Element.Bonuses);
			for (const auto& Points : Element.RacerPoints)
			{
				UE_LOG(LogTemp, Error, TEXT("%s"), *Points);
				if (Points.IsNumeric()) points += FCString::Atoi(*Points);
				races++;
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("Overall points %f"), points);
		UE_LOG(LogTemp, Warning, TEXT("Overall races %i"), races);
		UE_LOG(LogTemp, Warning, TEXT("avg %f"), points / races);
	}
}

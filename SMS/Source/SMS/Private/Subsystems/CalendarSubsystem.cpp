
#include "Subsystems/CalendarSubsystem.h"


void UCalendarSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	BindDelegate();
}


void UCalendarSubsystem::BindDelegate()
{
	OnMatchCompletedDelegate.AddUObject(this, &UCalendarSubsystem::UpdateMatchStatus);
}


void UCalendarSubsystem::AddMatch(const FMatchData& Match)
{
	Matches.Add(Match);
	UE_LOG(LogTemp, Display, TEXT("%i"), Matches.Num());
}


void UCalendarSubsystem::UpdateMatchStatus(const FMatchData& MatchData)
{
	if (Matches.IsEmpty()) return;
	if (FMatchData* Data = Matches.FindByKey(MatchData)) Data->bCompleted = true;
	CheckWeekMatches();
}


void UCalendarSubsystem::CheckWeekMatches()
{
	if (Matches.IsEmpty()) return;
	int32 AmountOfMatches = 0;
	for (const auto& Match : Matches)
	{
		if (Match.MatchID.Week == CurrentWeek) AmountOfMatches++;
	}
	int32 AmountOfCompletedMatches = 0;
	for (const auto& Match : Matches)
	{
		if (Match.MatchID.Week > CurrentWeek) return;
		if (Match.MatchID.Week == CurrentWeek && Match.bCompleted) AmountOfCompletedMatches++;
		if (AmountOfMatches == AmountOfCompletedMatches)
		{
			CurrentWeek++;
			OnWeekChangedDelegate.Broadcast(CurrentWeek);
		}
	}
}

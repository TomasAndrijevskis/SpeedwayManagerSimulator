
#include "UI/Calendar/CalendarRound.h"
#include "Components/VerticalBox.h"
#include "UI/BaseClasses/NumbersBox.h"
#include "UI/Calendar/CalendarLine.h"


void UCalendarRound::SetRound(int32 NewRound)
{
	CurrentRound = NewRound;
	NumbersBox_Round->SetText(NewRound);
}


void UCalendarRound::CreateMatches(const TArray<FTeamsInMatch>& Matches)
{
	for (const auto& Match : Matches)
	{
		UCalendarLine* CalendarLine = CreateMatch(Match.HomeTeam, Match.VisitorTeam);
		if (!CalendarLine) return;
		VerticalBox_Content->AddChildToVerticalBox(CalendarLine);
	}
}


UCalendarLine* UCalendarRound::CreateMatch(ETeams HomeTeam, ETeams VisitorTeam)
{
	if (!CalendarLineClass) return nullptr;
	UCalendarLine* CalendarLine = CreateWidget<UCalendarLine>(this, CalendarLineClass);
	if (!CalendarLine) return nullptr;
	CalendarLine->InitializeLine(HomeTeam, VisitorTeam);
	return CalendarLine;
}

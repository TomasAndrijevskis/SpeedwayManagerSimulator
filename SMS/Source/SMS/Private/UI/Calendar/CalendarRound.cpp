
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
		UCalendarLine* CalendarLine = CreateMatch(Match.HomeTeamID, Match.VisitorTeamID);
		if (!CalendarLine) return;
		VerticalBox_Content->AddChildToVerticalBox(CalendarLine);
	}
}


UCalendarLine* UCalendarRound::CreateMatch(int32 HomeTeam, int32 VisitorTeam)
{
	if (!CalendarLineClass) return nullptr;
	UCalendarLine* CalendarLine = CreateWidget<UCalendarLine>(this, CalendarLineClass);
	if (!CalendarLine) return nullptr;
	CalendarLine->InitializeLine(HomeTeam, VisitorTeam);
	return CalendarLine;
}

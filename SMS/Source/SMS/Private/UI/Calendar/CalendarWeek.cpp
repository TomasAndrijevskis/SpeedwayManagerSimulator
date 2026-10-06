
#include "UI/Calendar/CalendarWeek.h"
#include "Components/VerticalBox.h"
#include "UI/BaseClasses/CalendarLine_Base.h"
#include "UI/BaseClasses/NumbersBox.h"
#include "UI/Calendar/GP_CalendarLine.h"
#include "UI/Calendar/League_CalendarLine.h"


void UCalendarWeek::SetWeek(int32 NewWeek)
{
	NumbersBox_Round->SetText(NewWeek);
}


void UCalendarWeek::CreateMatches(const TArray<FTeamsInMatch>& Matches, FMatchData& MatchData)
{
	int32 WeekMatchNumber = MatchData.MatchID.WeekMatchNumber;
	for (const auto& Match : Matches)
	{
		MatchData.MatchID.WeekMatchNumber = WeekMatchNumber;
		ULeague_CalendarLine* CalendarLine = CreateMatch(Match.HomeTeamID, Match.VisitorTeamID, MatchData);
		if (!CalendarLine) return;
		VerticalBox_Content->AddChildToVerticalBox(CalendarLine);
		WeekMatchNumber++;
	}
}


ULeague_CalendarLine* UCalendarWeek::CreateMatch(int32 HomeTeam, int32 VisitorTeam, const FMatchData& MatchData)
{
	if (!League_CalendarLineClass) return nullptr;
	ULeague_CalendarLine* CalendarLine = CreateWidget<ULeague_CalendarLine>(this, League_CalendarLineClass);
	if (!CalendarLine) return nullptr;
	CalendarLine->SetMatchData(MatchData);
	CalendarLine->InitializeLine(HomeTeam, VisitorTeam);
	return CalendarLine;
}


void UCalendarWeek::CreateMatch(ECountries Location, int32 Round, const FMatchData& MatchData)
{
	if (!GP_CalendarLineClass) return;
	UGP_CalendarLine* CalendarLine = CreateWidget<UGP_CalendarLine>(this, GP_CalendarLineClass);
	if (!CalendarLine) return;
	CalendarLine->SetMatchData(MatchData);
	CalendarLine->InitializeLine(Location, Round);
	VerticalBox_Content->AddChildToVerticalBox(CalendarLine);
}


#include "UI/Calendar/Calendar.h"
#include "Components/VerticalBox.h"
#include "Gamemodes/SMS_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "SMS/Public/UI/League/Program/LeagueProgram.h"
#include "UI/Calendar/CalendarLine.h"


void UCalendar::NativeConstruct()
{
	Super::NativeConstruct();
	SetAmountOfMatches();
	for (int32 i = 0; i < AmountOfMatches; i++)
	{
		CreateMatches();
	}
}


void UCalendar::SetAmountOfMatches()
{
	ASMS_GameMode* GameMode = Cast<ASMS_GameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	AmountOfMatches = GameMode->GetTeamsAmount() / 2;
}


int32 UCalendar::GetRandomTeam()
{
	ASMS_GameMode* GameMode = Cast<ASMS_GameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return NULL;
	int32 NumberOfTeams = GameMode->GetTeamsAmount();
	if (NumberOfTeams <= 0) return NULL;
	int32 TeamID = FMath::RandRange(1, NumberOfTeams);
	return TeamID;
}


void UCalendar::SetTeamID(int32& Team)
{
	Team = GetRandomTeam();
	if (ChosenOptions.Contains(Team)) SetTeamID(Team);
	else ChosenOptions.Add(Team);
}


void UCalendar::CreateMatches()
{
	int32 TeamA;
	int32 TeamB;
	SetTeamID(TeamA);
	SetTeamID(TeamB);
	UCalendarLine* CalendarLine = CreateMatch(TeamA, TeamB);
	if (!CalendarLine) return;
	VB_Content->AddChildToVerticalBox(CalendarLine);
}


UCalendarLine* UCalendar::CreateMatch(int32 HomeTeamID, int32 VisitorTeamID)
{
	if (!CalendarLineClass) return nullptr;
	UCalendarLine* CalendarLine = CreateWidget<UCalendarLine>(this, CalendarLineClass);
	if (!CalendarLine) return nullptr;
	CalendarLine->InitializeLine(HomeTeamID, VisitorTeamID);
	return CalendarLine;
}

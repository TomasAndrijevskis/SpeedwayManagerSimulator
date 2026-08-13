
#include "UI/Calendar/Calendar.h"

#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Gamemodes/SMS_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "SMS/Public/UI/League/Program/LeagueProgram.h"
#include "UI/Calendar/CalendarLine.h"
#include "UI/League/Standings/StandingsWidget.h"
#include "UI/League/Statistics/StatisticsWidget.h"


void UCalendar::NativeConstruct()
{
	Super::NativeConstruct();
	SetAmountOfMatches();
	CreateCalendar();
	Button_OpenStatistics->OnClicked.AddUniqueDynamic(this, &UCalendar::CreateStatisticsWidget);
	Button_OpenStandings->OnClicked.AddUniqueDynamic(this, &UCalendar::CreateStandingsWidget);
}


void UCalendar::CreateCalendar()
{
	/*for (int32 i = 0; i < AmountOfMatches; i++)
	{
		CreateMatches();
	}
	ChosenOptions.Empty();
	for (int32 i = 0; i < AmountOfMatches; i++)
	{
		CreateMatches();
	}*/

	int32 TeamID;
	SetTeamID(TeamID);
	for (int32 i = 0; i < 2; i++)
	{
		CreateMatches(TeamID);
	}
	for (const auto& Element : ChosenOptions)
	{
		if (Element == TeamID) continue;
		CreateMatches(Element, TeamID);
	}
}


void UCalendar::CreateStatisticsWidget()
{
	if (!StatisticsWidgetClass) return;
	UStatisticsWidget* Widget = CreateWidget<UStatisticsWidget>(this, StatisticsWidgetClass);
	if (!Widget) return;
	Widget->InitializeStatisticsWidget();
	Widget->AddToViewport(0);
}

void UCalendar::CreateStandingsWidget()
{
	if (!StandingsWidgetClass) return;
	UStandingsWidget* Widget = CreateWidget<UStandingsWidget>(this, StandingsWidgetClass);
	if (!Widget) return;
	Widget->InitializeStandingsWidget();
	Widget->AddToViewport(0);
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

void UCalendar::CreateMatches(int32 TeamAID)
{
	int32 TeamB;
	SetTeamID(TeamB);
	UCalendarLine* CalendarLine = CreateMatch(TeamAID, TeamB);
	if (!CalendarLine) return;
	VB_Content->AddChildToVerticalBox(CalendarLine);
}


void UCalendar::CreateMatches(int32 TeamAID, int32 TeamBID)
{
	UCalendarLine* CalendarLine = CreateMatch(TeamAID, TeamBID);
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

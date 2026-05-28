
#include "UI/Calendar/Calendar.h"
#include "Components/VerticalBox.h"
#include "Gamemodes/SMS_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "SMS/Public/UI/League/Program/LeagueProgram.h"
#include "UI/Calendar/CalendarLine.h"


void UCalendar::NativeConstruct()
{
	Super::NativeConstruct();
	for (int i = 0; i < AmountOfMatches; i++)
	{
		CreateMatches();
	}
}


int UCalendar::GetRandomTeam()
{
	const ASMS_GameMode* GameMode = Cast<ASMS_GameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return NULL;
	int NumberOfTeams = GameMode->GetTeamsAmount();
	if (NumberOfTeams <= 0) return NULL;
	int TeamID = FMath::RandRange(1, NumberOfTeams);
	UE_LOG(LogTemp, Warning, TEXT("Team id: %i"), TeamID);
	return TeamID;
}


void UCalendar::CreateMatches()
{
	UCalendarLine* CalendarLine = CreateMatch(GetRandomTeam(), GetRandomTeam());
	if (!CalendarLine) return;
	VB_Content->AddChildToVerticalBox(CalendarLine);
}


UCalendarLine* UCalendar::CreateMatch(int HomeTeamID, int VisitorTeamID)
{
	if (!CalendarLineClass) return nullptr;
	UCalendarLine* CalendarLine = CreateWidget<UCalendarLine>(this, CalendarLineClass);
	if (!CalendarLine) return nullptr;
	CalendarLine->SetMatchTeamsID(HomeTeamID, VisitorTeamID);
	return CalendarLine;
	/*if (!GameMode || !MatchManager) return;
	/*FText HTeamName  = StaticEnum<ETeams>()->GetDisplayNameTextByValue(HomeTeamData->TeamID);
	FText VTeamName = StaticEnum<ETeams>()->GetDisplayNameTextByValue(VisitorTeamData->TeamID);
	UE_LOG(LogTemp, Warning, TEXT("Home team: %s"), *HTeamName.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Visitor team: %s"), *VTeamName.ToString());
	NamesBox_HomeText->SetName("Home Team");
	NamesBox_VisitorText->SetName("Visitor Team");
	NamesBox_HomeTeamName->SetName(GameMode->GetTeamName(HomeTeamID)->ToString());
	NamesBox_VisitorTeamName->SetName(GameMode->GetTeamName(VisitorTeamID)->ToString());*/
}


#include "UI/Calendar/CalendarLine.h"
#include "Components/Button.h"
#include "Gamemodes/SMS_GameMode.h"
#include "Managers/MatchManager.h"
#include "Kismet/GameplayStatics.h"
#include "UI/BaseClasses/NamesBox.h"
#include "UI/League/Program/LeagueProgram.h"


void UCalendarLine::NativeConstruct()
{
	Super::NativeConstruct();
	Button_StartMatch->OnClicked.AddUniqueDynamic(this, &UCalendarLine::StartMatch);
}


void UCalendarLine::InitializeLine(int NewHomeTeamID, int NewVisitorTeamID)
{
	ASMS_GameMode* GameMode = Cast<ASMS_GameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	MatchManager = GameMode->GetMatchManager();
	if (!MatchManager) return;
	SetMatchTeamID(NewHomeTeamID, NewVisitorTeamID);
	DisplayTeamNames(GameMode->GetTeamName(HomeTeamID), GameMode->GetTeamName(VisitorTeamID));
}


void UCalendarLine::StartMatch()
{
	if (!LeagueProgramClass || !MatchManager) return;
	ULeagueProgram* LeagueProgram = CreateWidget<ULeagueProgram>(this, LeagueProgramClass);
	if (!LeagueProgram) return;
	MatchManager->SetTeamID(HomeTeamID, false);
	MatchManager->SetTeamID(VisitorTeamID, true);
	LeagueProgram->InitializeManagers();
	LeagueProgram->AddToViewport(1);
}


void UCalendarLine::DisplayTeamNames(const FText& HomeTeamName, const FText& VisitorTeamName)
{
	NamesBox_HomeTeamName->SetText(HomeTeamName);
	NamesBox_VisitorTeamName->SetText(VisitorTeamName);
}


void UCalendarLine::SetMatchTeamID(int NewHomeTeamID, int NewVisitorTeamID)
{
	HomeTeamID = NewHomeTeamID;
	VisitorTeamID = NewVisitorTeamID;
}
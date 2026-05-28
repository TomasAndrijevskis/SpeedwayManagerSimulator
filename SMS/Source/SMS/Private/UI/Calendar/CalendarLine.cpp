
#include "UI/Calendar/CalendarLine.h"
#include "Components/Button.h"
#include "Gamemodes/SMS_GameMode.h"
#include "Gamemodes/Managers/MatchManager.h"
#include "Kismet/GameplayStatics.h"
#include "UI/BaseClasses/NamesBox.h"
#include "UI/League/Program/LeagueProgram.h"


void UCalendarLine::NativeConstruct()
{
	Super::NativeConstruct();
	GameMode = Cast<ASMS_GameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	MatchManager = GameMode->MatchManager;
	if (!MatchManager) return;
	Button_StartMatch->OnClicked.AddUniqueDynamic(this, &UCalendarLine::StartMatch);
	SetTeamNames();
}


void UCalendarLine::StartMatch()
{
	if (!LeagueProgramClass || !GameMode || !MatchManager) return;
	ULeagueProgram* LeagueProgram = CreateWidget<ULeagueProgram>(this, LeagueProgramClass);
	if (!LeagueProgram) return;
	LeagueProgram->AddToViewport(1);
	MatchManager->OnMatchStartedDelegate.Broadcast(GameMode->GetTeamData(HomeTeamID), GameMode->GetTeamData(VisitorTeamID));
	//FText HTeamName  = StaticEnum<ETeams>()->GetDisplayNameTextByValue(HomeTeamData->TeamID);
	//FText VTeamName = StaticEnum<ETeams>()->GetDisplayNameTextByValue(VisitorTeamData->TeamID);
	//LeagueProgram->CreateTeam(false, HTeamName.ToString());
	//LeagueProgram->CreateTeam(true, VTeamName.ToString());
}


void UCalendarLine::SetTeamNames()
{
	if (!GameMode) return;
	NamesBox_HomeTeamName->SetName(GameMode->GetTeamName(HomeTeamID)->ToString());
	NamesBox_VisitorTeamName->SetName(GameMode->GetTeamName(VisitorTeamID)->ToString());
}


void UCalendarLine::SetMatchTeamsID(int NewHomeTeamID, int NewVisitorTeamID){HomeTeamID = NewHomeTeamID; VisitorTeamID = NewVisitorTeamID;}

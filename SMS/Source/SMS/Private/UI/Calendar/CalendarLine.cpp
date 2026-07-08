
#include "UI/Calendar/CalendarLine.h"
#include "Components/Button.h"
#include "Gamemodes/SMS_GameMode.h"
#include "Managers/MatchManager.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/ScoreManager.h"
#include "UI/BaseClasses/NamesBox.h"
#include "UI/BaseClasses/NumbersBox.h"
#include "UI/League/Program/LeagueProgram.h"


void UCalendarLine::NativeConstruct()
{
	Super::NativeConstruct();
	Button_StartMatch->OnClicked.AddUniqueDynamic(this, &UCalendarLine::InitializeManagers);
}


void UCalendarLine::InitializeManagers()
{
	ASMS_GameMode* GameMode = Cast<ASMS_GameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	GameMode->CreateRequiredManagers();
	MatchManager = GameMode->GetMatchManager();
	ScoreManager = GameMode->GetScoreManager();
	if (!MatchManager || !ScoreManager) return;
	MatchManager->OnMatchEndedDelegate.AddUObject(this, &UCalendarLine::OnMatchEnded);
	StartMatch();
}


void UCalendarLine::InitializeLine(int NewHomeTeamID, int NewVisitorTeamID)
{
	ASMS_GameMode* GameMode = Cast<ASMS_GameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	SetMatchTeamID(NewHomeTeamID, NewVisitorTeamID);
	DisplayTeamNames(GameMode->GetTeamName(HomeTeamID), GameMode->GetTeamName(VisitorTeamID));
}


void UCalendarLine::OnMatchEnded()
{
	ASMS_GameMode* GameMode = Cast<ASMS_GameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	Button_StartMatch->OnClicked.Clear();
	Button_StartMatch->SetIsEnabled(false);
	if (!ScoreManager) return;
	DisplayFinalScore(ScoreManager->GetTeamScore(false), ScoreManager->GetTeamScore(true));
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


void UCalendarLine::DisplayFinalScore(int HomePoints, int VisitorPoints)
{
	NumbersBox_HomeTeamScore->SetText(HomePoints);
	NumbersBox_VisitorTeamScore->SetText(VisitorPoints);
}


void UCalendarLine::SetMatchTeamID(int NewHomeTeamID, int NewVisitorTeamID)
{
	HomeTeamID = NewHomeTeamID;
	VisitorTeamID = NewVisitorTeamID;
}
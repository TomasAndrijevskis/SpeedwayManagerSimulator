
#include "UI/Calendar/CalendarLine.h"
#include "Components/Button.h"
#include "Gamemodes/SMS_GameMode.h"
#include "Managers/MatchManager.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/ScoreManager.h"
#include "UI/BaseClasses/NamesBox.h"
#include "UI/BaseClasses/NumbersBox.h"
#include "UI/BaseClasses/Program_Base.h"


void UCalendarLine::NativeConstruct()
{
	Super::NativeConstruct();
	Button_StartMatch->OnClicked.AddUniqueDynamic(this, &UCalendarLine::InitializeManagers);
}


void UCalendarLine::InitializeManagers()
{
	ASMS_GameMode* GameMode = Cast<ASMS_GameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	GameMode->CreateManagers();
	MatchManager = GameMode->GetMatchManager();
	if (!MatchManager) return;
	ScoreManager = MatchManager->GetScoreManager();
	MatchManager->OnMatchEndedDelegate.AddUObject(this, &UCalendarLine::OnMatchEnded);
	StartMatch();
}


void UCalendarLine::InitializeLine(int32 HomeTeamID, int32 VisitorTeamID)
{
	ASMS_GameMode* GameMode = Cast<ASMS_GameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	ETeams NewHomeTeam = static_cast<ETeams>(HomeTeamID);
	ETeams NewVisitorTeam = static_cast<ETeams>(VisitorTeamID);
	SetMatchTeams(NewHomeTeam, NewVisitorTeam);
	DisplayTeamNames(GameMode->GetTeamName(HomeTeam), GameMode->GetTeamName(VisitorTeam));
}


void UCalendarLine::OnMatchEnded()
{
	if (!ScoreManager) return;
	Button_StartMatch->OnClicked.Clear();
	Button_StartMatch->SetIsEnabled(false);
	DisplayFinalScore(ScoreManager->GetTeamScore(false), ScoreManager->GetTeamScore(true));
	ScoreManager = nullptr;
	MatchManager = nullptr;
}


void UCalendarLine::StartMatch()
{
	if (!ProgramClass || !MatchManager) return;
	UProgram* Program = CreateWidget<UProgram>(this, ProgramClass);
	if (!Program) return;
	MatchManager->SetTeam(HomeTeam, false);
	MatchManager->SetTeam(VisitorTeam, true);
	Program->InitializeManagers();
	Program->AddToViewport(1);
}


void UCalendarLine::DisplayTeamNames(const FString& HomeTeamName, const FString& VisitorTeamName)
{
	NamesBox_HomeTeamName->SetText(HomeTeamName);
	NamesBox_VisitorTeamName->SetText(VisitorTeamName);
}


void UCalendarLine::DisplayFinalScore(int32 HomePoints, int32 VisitorPoints)
{
	NumbersBox_HomeTeamScore->SetText(HomePoints);
	NumbersBox_VisitorTeamScore->SetText(VisitorPoints);
}


void UCalendarLine::SetMatchTeams(ETeams NewHomeTeam, ETeams NewVisitorTeam)
{
	HomeTeam = NewHomeTeam;
	VisitorTeam = NewVisitorTeam;
}
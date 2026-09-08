
#include "UI/Calendar/CalendarLine.h"
#include "Components/Button.h"
#include "Gamemodes/SMS_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Rules/LeagueRules.h"
#include "Subsystems/MatchManagerSubsystem.h"
#include "UI/BaseClasses/NamesBox.h"
#include "UI/BaseClasses/NumbersBox.h"
#include "UI/BaseClasses/Program_Base.h"


void UCalendarLine::NativeConstruct()
{
	Super::NativeConstruct();
	Button_StartMatch->OnClicked.AddUniqueDynamic(this, &UCalendarLine::StartMatch);
}



void UCalendarLine::StartMatch()
{
	if (UMatchManagerSubsystem* MatchManagerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMatchManagerSubsystem>())
	{
		MatchManagerSubsystem->StartMatch(ULeagueRules::StaticClass());
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		MatchManagerSubsystem->GetCompetitionRules()->OnMatchFinishedDelegate.AddUObject(this, &UCalendarLine::OnMatchEnded);
		
		if (!ProgramClass) return;
		UProgram* Program = CreateWidget<UProgram>(this, ProgramClass);
		if (!Program) return;
		Cast<ULeagueRules>(MatchManagerSubsystem->GetCompetitionRules())->SetTeam(HomeTeam, false);
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		Cast<ULeagueRules>(MatchManagerSubsystem->GetCompetitionRules())->SetTeam(VisitorTeam, true);
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		Program->AddToViewport(1);
	}
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
	Button_StartMatch->OnClicked.Clear();
	Button_StartMatch->SetIsEnabled(false);
	if (UMatchManagerSubsystem* MatchManagerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMatchManagerSubsystem>())
	{
		if (ULeagueRules* Rules = Cast<ULeagueRules>(MatchManagerSubsystem->GetCompetitionRules()))
		{
			DisplayFinalScore(Rules->GetTeamScore(false), Rules->GetTeamScore(true));
		}
	}
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
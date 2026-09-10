
#include "UI/Calendar/CalendarLine.h"
#include "Components/Button.h"
#include "Gamemodes/SMS_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Rules/League_Rules.h"
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
		MatchManagerSubsystem->StartMatch(ULeague_Rules::StaticClass());
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		MatchManagerSubsystem->GetCompetitionRules()->OnRacingFinishedDelegate.AddUObject(this, &UCalendarLine::CollectMatchScore);
		
		if (!ProgramClass) return;
		UProgram* Program = CreateWidget<UProgram>(this, ProgramClass);
		if (!Program) return;
		Cast<ULeague_Rules>(MatchManagerSubsystem->GetCompetitionRules())->SetTeam(HomeTeam, false);
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		Cast<ULeague_Rules>(MatchManagerSubsystem->GetCompetitionRules())->SetTeam(VisitorTeam, true);
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


void UCalendarLine::CollectMatchScore()
{
	if (UMatchManagerSubsystem* MatchManagerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMatchManagerSubsystem>())
	{
		MatchManagerSubsystem->GetCompetitionRules()->OnMatchClosedDelegate.AddUObject(this, &UCalendarLine::OnMatchEnded);
		if (ULeague_Rules* Rules = Cast<ULeague_Rules>(MatchManagerSubsystem->GetCompetitionRules()))
		{
			HomeTeamScore = Rules->GetTeamScore(false);
			VisitorTeamScore = Rules->GetTeamScore(true);
		}
	}
}


void UCalendarLine::OnMatchEnded()
{
	DisplayFinalScore(HomeTeamScore, VisitorTeamScore);
	Button_StartMatch->OnClicked.Clear();
	Button_StartMatch->SetIsEnabled(false);
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

#include "UI/League/Program/League_Program.h"
#include "Components/BackgroundBlur.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Rules/LeagueRules.h"
#include "Subsystems/MatchManagerSubsystem.h"
#include "UI/League/Program/TeamRoster.h"


void ULeague_Program::NativeConstruct()
{
	Super::NativeConstruct();
	BindDelegates();
	CreateRaces();
	InitializeTeams();
	CreateRaceStatsWidget();
	ShowTeams();
}


void ULeague_Program::BindDelegates()
{
	Super::BindDelegates();
	Button_ConfirmRacers->OnClicked.AddUniqueDynamic(this, &ULeague_Program::PopulateRacers);
	Button_ShowTeams->OnClicked.AddUniqueDynamic(this, &ULeague_Program::ShowTeams);
	Button_RandomizeTeamRosters->OnClicked.AddUniqueDynamic(this, &ULeague_Program::RandomizeTeamRosters);
}


void ULeague_Program::RandomizeTeamRosters()
{
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	if (UMatchManagerSubsystem* MatchManagerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMatchManagerSubsystem>())
	{
		if (ULeagueRules* Rules = Cast<ULeagueRules>(MatchManagerSubsystem->GetCompetitionRules()))
		{
			Rules->MakeRandomRosters();
		}
	}
}


void ULeague_Program::InitializeTeams()
{
	CreateTeamRoster(false);
	CreateTeamRoster(true);
}


void ULeague_Program::CreateTeamRoster(bool IsVisitor)
{
	if (!TeamRosterClass) return;
	UTeamRoster* TeamRoster = CreateWidget<UTeamRoster>(this, TeamRosterClass);
	if (!TeamRoster) return;
	TeamRoster->InitializeTeam(IsVisitor);
	VB_Teams->AddChild(TeamRoster);
}


void ULeague_Program::ShowTeams()
{
	if (VB_Teams->IsVisible())
	{
		VB_Teams->SetVisibility(ESlateVisibility::Hidden);
		BackgroundBlur->SetBlurStrength(0);
	}
	else
	{
		VB_Teams->SetVisibility(ESlateVisibility::Visible);
		BackgroundBlur->SetBlurStrength(15.f);
	}
}


void ULeague_Program::PopulateRacers()
{
	if (UMatchManagerSubsystem* MatchManagerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMatchManagerSubsystem>())
	{
		if (MatchManagerSubsystem->GetCompetitionRules()->CanStartMatch())
		{
			DisableButtons();
			ShowTeams();
			MatchManagerSubsystem->GetCompetitionRules()->PopulateRacers();
		}
	}
}


void ULeague_Program::DisableButtons()
{
	Button_RandomizeTeamRosters->SetIsEnabled(false);
	Button_ConfirmRacers->SetIsEnabled(false);
}
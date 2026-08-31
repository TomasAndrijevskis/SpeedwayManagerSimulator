
#include "SMS/Public/UI/League/Program/LeagueProgram.h"
#include "Components/BackgroundBlur.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Managers/MatchManager.h"
#include "Managers/TeamManager.h"
#include "Subsystems/RulesSubsystem.h"
#include "UI/League/Program/TeamRoster.h"
#include "UI/League/Program/Race/RaceStats/RaceStats.h"


void ULeagueProgram::NativeConstruct()
{
	Super::NativeConstruct();
	BindDelegates();
	InitializeTeams();
	CreateRaces();
	CreateRaceStatsWidget();
	ShowTeams();
}


void ULeagueProgram::BindDelegates()
{
	Super::BindDelegates();
	Button_ShowTeams->OnClicked.AddUniqueDynamic(this, &ULeagueProgram::ShowTeams);
	Button_RandomizeTeamRosters->OnClicked.AddUniqueDynamic(this, &ULeagueProgram::RandomizeTeamRosters);
}


void ULeagueProgram::DisableButtons()
{
	Button_ConfirmRacers->SetIsEnabled(false);
	Button_RandomizeTeamRosters->SetIsEnabled(false);
}


void ULeagueProgram::CreateRaceStatsWidget()
{
	if (!RaceStatsWidget) return;
	RaceStatsWidget->InitializeWidget();
}


void ULeagueProgram::CollectStatistics()
{
	if (URulesSubsystem* Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<URulesSubsystem>())
	{
		Subsystem->DecideMatchWinner(TeamManagers);
	}
	for (const auto& Team : TeamManagers)
	{
		for (const auto& Racer : Team->GetRacerManagers())
		{
			Racer.Value->CollectMatchStatistics();
		}
	}
}


void ULeagueProgram::RandomizeTeamRosters()
{
	for (const auto& Roster : TeamManagers)
	{
		Roster->MakeRandomTeamRoster();
	}
}


void ULeagueProgram::InitializeTeams()
{
	if (!MatchManager) return;
	UTeamRoster* Home = CreateTeamRoster(MatchManager->GetTeamData(false));
	UTeamRoster* Visitor = CreateTeamRoster(MatchManager->GetTeamData(true));
	RegisterTeamRoster(Home);
	RegisterTeamRoster(Visitor);
}


UTeamRoster* ULeagueProgram::CreateTeamRoster(FTeamMatchData* TeamData)
{
	if (!TeamRosterClass || !MatchManager) return nullptr;
	UTeamRoster* TeamRoster = CreateWidget<UTeamRoster>(this, TeamRosterClass);
	if (!TeamRoster) return nullptr;
	TeamRoster->InitializeTeam(TeamData, MatchManager);
	return TeamRoster;
}


void ULeagueProgram::RegisterTeamRoster(UTeamRoster* TeamRoster)
{
	if (!TeamRoster) return;
	VB_Teams->AddChild(TeamRoster);
	TeamManagers.Add(TeamRoster->GetTeamManager());
}


void ULeagueProgram::ShowTeams()
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


void ULeagueProgram::PopulateRacers()
{
	if (!MatchManager || TeamManagers.IsEmpty()) return;
	for (const auto& Manager : TeamManagers)
	{
		if (!Manager->IsRosterValid()) return;
	}
	for (const auto& Manager : TeamManagers)
	{
		Manager->LockChosenRacers();
	}
	MatchManager->CreateRacerManagers(TeamManagers);
	DisableButtons();
	ShowTeams();
}
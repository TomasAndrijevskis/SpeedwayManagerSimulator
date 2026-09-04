
#include "UI/League/Program/League_Program.h"
#include "Components/BackgroundBlur.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Managers/TeamManager.h"
#include "Rules/LeagueRules.h"
#include "Subsystems/MatchManagerSubsystem.h"
#include "Subsystems/RulesSubsystem.h"
#include "UI/League/Program/TeamRoster.h"


void ULeague_Program::NativeConstruct()
{
	Super::NativeConstruct();
	BindDelegates();
	InitializeTeams();
	CreateRaces();
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


void ULeague_Program::CollectStatistics()
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


void ULeague_Program::RandomizeTeamRosters()
{
	for (const auto& Roster : TeamManagers)
	{
		Roster->MakeRandomTeamRoster();
	}
}


void ULeague_Program::InitializeTeams()
{
	if (UMatchManagerSubsystem* MatchManagerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMatchManagerSubsystem>())
	{
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		UTeamRoster* Home = CreateTeamRoster(Cast<ULeagueRules>(MatchManagerSubsystem->GetCompetitionRules())->GetTeamData(false));
		UTeamRoster* Visitor = CreateTeamRoster(Cast<ULeagueRules>(MatchManagerSubsystem->GetCompetitionRules())->GetTeamData(true));
		RegisterTeamRoster(Home);
		RegisterTeamRoster(Visitor);
	}
}


UTeamRoster* ULeague_Program::CreateTeamRoster(FTeamMatchData* TeamData)
{
	if (!TeamRosterClass) return nullptr;
	UTeamRoster* TeamRoster = CreateWidget<UTeamRoster>(this, TeamRosterClass);
	if (!TeamRoster) return nullptr;
	TeamRoster->InitializeTeam(TeamData);
	return TeamRoster;
}


void ULeague_Program::RegisterTeamRoster(UTeamRoster* TeamRoster)
{
	if (!TeamRoster) return;
	VB_Teams->AddChild(TeamRoster);
	TeamManagers.Add(TeamRoster->GetTeamManager());
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
	if (TeamManagers.IsEmpty()) return;
	for (const auto& Manager : TeamManagers)
	{
		if (!Manager->IsRosterValid()) return;
	}
	for (const auto& Manager : TeamManagers)
	{
		Manager->LockChosenRacers();
	}
	if (UMatchManagerSubsystem* MatchManagerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMatchManagerSubsystem>())
	{
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		Cast<ULeagueRules>(MatchManagerSubsystem->GetCompetitionRules())->CreateRacerManagers(TeamManagers);
	}
	DisableButtons();
	ShowTeams();
}


void ULeague_Program::DisableButtons()
{
	Button_RandomizeTeamRosters->SetIsEnabled(false);
	Button_ConfirmRacers->SetIsEnabled(false);
}
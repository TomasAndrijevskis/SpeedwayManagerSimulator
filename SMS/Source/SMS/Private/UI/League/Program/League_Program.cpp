
#include "UI/League/Program/League_Program.h"
#include "Components/BackgroundBlur.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Managers/MatchManager.h"
#include "Managers/TeamManager.h"
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


void ULeague_Program::DisableButtons()
{
	Super::DisableButtons();
	Button_RandomizeTeamRosters->SetIsEnabled(false);
}


void ULeague_Program::InitializeTeams()
{
	if (!MatchManager) return;
	UTeamRoster* Home = CreateTeamRoster(MatchManager->GetTeamData(false));
	UTeamRoster* Visitor = CreateTeamRoster(MatchManager->GetTeamData(true));
	RegisterTeamRoster(Home);
	RegisterTeamRoster(Visitor);
}


UTeamRoster* ULeague_Program::CreateTeamRoster(FTeamMatchData* TeamData)
{
	if (!TeamRosterClass || !MatchManager) return nullptr;
	UTeamRoster* TeamRoster = CreateWidget<UTeamRoster>(this, TeamRosterClass);
	if (!TeamRoster) return nullptr;
	TeamRoster->InitializeTeam(TeamData, MatchManager);
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
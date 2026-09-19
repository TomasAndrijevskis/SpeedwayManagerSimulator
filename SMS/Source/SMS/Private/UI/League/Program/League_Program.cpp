
#include "UI/League/Program/League_Program.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Subsystems/MatchManagerSubsystem.h"
#include "UI/League/Program/TeamRoster.h"


void ULeague_Program::NativeConstruct()
{
	Super::NativeConstruct();
	BindDelegates();
	CreateRaces();
	InitializeTeams();
	CreateRaceStatsWidget();
	ShowLineup();
}


void ULeague_Program::BindDelegates()
{
	Super::BindDelegates();
	Button_RandomizeRacers->OnClicked.AddUniqueDynamic(this, &ULeague_Program::RandomizeRacers);
}


void ULeague_Program::RandomizeRacers()
{
	if (UMatchManagerSubsystem* MatchManagerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMatchManagerSubsystem>())
	{
		MatchManagerSubsystem->GetCompetitionRules()->MakeRandomRosters();
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
	VB_Lineup->AddChild(TeamRoster);
}


void ULeague_Program::PopulateRacers()
{
	if (UMatchManagerSubsystem* MatchManagerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMatchManagerSubsystem>())
	{
		if (MatchManagerSubsystem->GetCompetitionRules()->CanStartMatch())
		{
			DisableButtons();
			ShowLineup();
			MatchManagerSubsystem->GetCompetitionRules()->PopulateRacers();
		}
	}
}


void ULeague_Program::DisableButtons()
{
	Button_RandomizeRacers->SetIsEnabled(false);
	Button_ConfirmRacers->SetIsEnabled(false);
}
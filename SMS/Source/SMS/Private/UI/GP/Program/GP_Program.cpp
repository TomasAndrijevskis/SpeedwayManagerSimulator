
#include "UI/GP/Program/GP_Program.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Subsystems/MatchManagerSubsystem.h"
#include "UI/GP/Program/GP_Lineup.h"


void UGPProgram::NativeConstruct()
{
	Super::NativeConstruct();
	BindDelegates();
	RandomizeRacers();
	CreateRaces();
	CreateRaceStatsWidget();
	CreateLineup();
	ShowLineup();
}


void UGPProgram::RandomizeRacers()
{
	if (UMatchManagerSubsystem* MatchManagerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMatchManagerSubsystem>())
	{
		MatchManagerSubsystem->GetCompetitionRules()->MakeRandomRosters();
	}
}


void UGPProgram::CreateLineup()
{
	if (!LineupClass) return;
	UGP_Lineup* Lineup = Cast<UGP_Lineup>(CreateWidget(this, LineupClass));
	if (!Lineup) return;
	Button_ShowRacers->OnClicked.AddUniqueDynamic(Lineup, &UGP_Lineup::SortLines);
	VB_Lineup->AddChild(Lineup);
}


void UGPProgram::DisableButtons()
{
	Button_ConfirmRacers->SetIsEnabled(false);
}


void UGPProgram::PopulateRacers()
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

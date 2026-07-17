
#include "SMS/Public/UI/League/Program/LeagueProgram.h"
#include "Components/BackgroundBlur.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Gamemodes/SMS_GameMode.h"
#include "Managers/MatchManager.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/TeamManager.h"
#include "SMS/Public/UI/League/Program/Race.h"
#include "SMS/Public/UI/League/Program/TeamRoster.h"


void ULeagueProgram::NativeConstruct()
{
	Super::NativeConstruct();
	BindDelegates();
	InitializeTeams();
	CreateRaces();
	ShowTeams();
}


void ULeagueProgram::InitializeManagers()
{
	ASMS_GameMode* GameMode = Cast<ASMS_GameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	MatchManager = GameMode->GetMatchManager();
}


void ULeagueProgram::BindDelegates()
{
	if (!MatchManager) return;
	Button_ConfirmTeams->OnClicked.AddUniqueDynamic(this, &ULeagueProgram::PopulateRacers);
	Button_ConfirmTeams->OnClicked.AddUniqueDynamic(this, &ULeagueProgram::DisableButtons);
	Button_ShowTeams->OnClicked.AddUniqueDynamic(this, &ULeagueProgram::ShowTeams);
	Button_RandomizeTeamRosters->OnClicked.AddUniqueDynamic(this, &ULeagueProgram::RandomizeTeamRosters);
	Button_SimulateRace->OnClicked.AddUniqueDynamic(this, &ULeagueProgram::StartRace);
	MatchManager->OnMatchEndedDelegate.AddUObject(this, &ULeagueProgram::ChangeButtonBehaviour);
}


void ULeagueProgram::DisableButtons()
{
	Button_ConfirmTeams->SetIsEnabled(false);
	Button_RandomizeTeamRosters->SetIsEnabled(false);
}


void ULeagueProgram::ChangeButtonBehaviour()
{
	Text_SimulateButton->SetText(FText::FromString("End match"));
	Button_SimulateRace->OnClicked.Clear();
	Button_SimulateRace->OnClicked.AddUniqueDynamic(this, &ULeagueProgram::FinishMatch);
}


void ULeagueProgram::FinishMatch()
{
	this->RemoveFromParent();
}


void ULeagueProgram::StartRace()
{
	if (!MatchManager) return;
	MatchManager->OnRaceStaredDelegate.Broadcast();
}


void ULeagueProgram::RandomizeTeamRosters()
{
	for (const auto& Roster : TeamManagers)
	{
		Roster->RandomizeTeamRoster();
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
	if (!TeamRosterClass) return nullptr;
	UTeamRoster* TeamRoster = CreateWidget<UTeamRoster>(this, TeamRosterClass);
	if (!TeamRoster) return nullptr;
	TeamRoster->InitializeTeam(TeamData);
	return TeamRoster;
}


void ULeagueProgram::RegisterTeamRoster(UTeamRoster* TeamRoster)
{
	if (!TeamRoster) return;
	VB_Teams->AddChild(TeamRoster);
	TeamManagers.Add(TeamRoster->GetTeamManager());
}


void ULeagueProgram::CreateRaces()
{
	if (!MatchManager) return;
	FVector2d TempPosition = StartPosition;
	FAnchors StartAnchors(0.0f, 0.5f, 0.0f, 0.5f);
	FVector2d StartAlignment = FVector2d(0, 0);
	for (int RaceID = 1; RaceID <= AmountOfRaces; RaceID++)
	{
		const float PositionOffset = 162.0f;
		const float Offset = 0.5f;
		URace* NewRace = CreateRace(StartAnchors, TempPosition, StartAlignment);
		if (NewRace)
		{
			NewRace->InitializeWidget(RaceID);
			MatchManager->AddNewRace(RaceID, NewRace->GetRaceData());
		}
		TempPosition.Y += PositionOffset;
		if (RaceID % 5 == 0)
		{
			TempPosition = StartPosition;
			StartAnchors.Minimum.X += Offset;
			StartAnchors.Maximum.X += Offset;
			StartAlignment.X += Offset;
		}
	}
}


URace* ULeagueProgram::CreateRace(const FAnchors& Anchors, const FVector2d& Position, const FVector2d& Alignment)
{
	if (!RaceClass) return nullptr;
	URace* NewRace = CreateWidget<URace>(this, RaceClass);
	if (!NewRace) return nullptr;
	UCanvasPanelSlot* RaceSlot = CanvasPanel_Root->AddChildToCanvas(NewRace);
	if (RaceSlot)
	{
		RaceSlot->SetAnchors(Anchors);
		RaceSlot->SetPosition(Position);
		RaceSlot->SetAlignment(Alignment);
		RaceSlot->SetAutoSize(true);
	}
	return NewRace;
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
	if (!MatchManager) return;
	MatchManager->CreateRacerManagers(TeamManagers);
}
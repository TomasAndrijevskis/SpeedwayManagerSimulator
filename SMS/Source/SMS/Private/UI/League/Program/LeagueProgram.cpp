
#include "SMS/Public/UI/League/Program/LeagueProgram.h"
#include "Components/BackgroundBlur.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/VerticalBox.h"
#include "Gamemodes/SMS_GameMode.h"
#include "Managers/MatchManager.h"
#include "Kismet/GameplayStatics.h"
#include "SMS/Public/UI/League/Program/Race.h"
#include "SMS/Public/UI/League/Program/TeamRoster.h"
#include "UI/League/Program/NominatedRaceWidgets/FillNominatedRaces.h"


void ULeagueProgram::NativeConstruct()
{
	Super::NativeConstruct();
	InitializeManagers();
	BindDelegates();
	InitializeTeams();
	CreateRaces();
	ShowTeams();
}


void ULeagueProgram::InitializeManagers()
{
	ASMS_GameMode* GameMode = Cast<ASMS_GameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	MatchManager = GameMode->MatchManager;
}


void ULeagueProgram::BindDelegates()
{
	Button_ConfirmTeams->OnClicked.AddUniqueDynamic(this, &ULeagueProgram::PopulateRacers);
	Button_ShowTeams->OnClicked.AddUniqueDynamic(this, &ULeagueProgram::ShowTeams);
	Button_RandomizeTeamRosters->OnClicked.AddUniqueDynamic(this, &ULeagueProgram::RandomizeTeamRosters);
	BindSimulateButtonAction(false);
	if (!MatchManager) return;
	MatchManager->OnNominatedRacesStaredDelegate.AddUObject(this, &ULeagueProgram::BindSimulateButtonAction);
}


void ULeagueProgram::StartRace()
{
	if (!MatchManager) return;
	MatchManager->OnRaceStaredDelegate.Broadcast();
}


void ULeagueProgram::BindSimulateButtonAction(const bool IsNominatedRace)
{
	if (IsNominatedRace)
	{
		Button_SimulateRace->OnClicked.Clear();
		Button_SimulateRace->OnClicked.AddUniqueDynamic(this, &ULeagueProgram::FillNominatedRaces);
	}
	else
	{
		Button_SimulateRace->OnClicked.Clear();
		Button_SimulateRace->OnClicked.AddUniqueDynamic(this, &ULeagueProgram::StartRace);
	}
}


void ULeagueProgram::RandomizeTeamRosters()
{
	for (const auto& Roster : TeamRosters)
	{
		Roster->RandomizeTeamRoster();
	}
}


void ULeagueProgram::FillNominatedRaces()
{
	if (!FillNominatedRacesClass) return;
	UFillNominatedRaces* FillNominatedRaces = CreateWidget<UFillNominatedRaces>(this, FillNominatedRacesClass);
	if (!FillNominatedRaces) return;
	FillNominatedRaces->InitializeManagers();
			FillNominatedRaces->InitializeWidget();
	FillNominatedRaces->AddToViewport(2);
	FillNominatedRaces->OnConfirmedDelegate.AddUObject(this, &ULeagueProgram::BindSimulateButtonAction);
}


void ULeagueProgram::InitializeTeams()
{
	if (!MatchManager) return;
	UTeamRoster* Home = CreateTeamRoster(MatchManager->GetHomeTeamID(), false);
	UTeamRoster* Visitor = CreateTeamRoster(MatchManager->GetVisitorTeamID(), true);
	RegisterTeamRoster(Home);
	RegisterTeamRoster(Visitor);
}


UTeamRoster* ULeagueProgram::CreateTeamRoster(int TeamID, bool IsVisitor)
{
	if (!TeamRosterClass) return nullptr;
	UTeamRoster* TeamRoster = CreateWidget<UTeamRoster>(this, TeamRosterClass);
	if (!TeamRoster) return nullptr;
	TeamRoster->InitializeTeam(TeamID, IsVisitor);
	return TeamRoster;
}


void ULeagueProgram::RegisterTeamRoster(UTeamRoster* TeamRoster)
{
	if (!TeamRoster) return;
	VB_Teams->AddChild(TeamRoster);
	TeamRosters.Add(TeamRoster);
}


void ULeagueProgram::CreateRaces()
{
	if (!MatchManager) return;
	FVector2d TempPosition = StartPosition;
	FAnchors StartAnchors(0.0f, 0.5f, 0.0f, 0.5f);
	FVector2d StartAlignment = FVector2d(0, 0);
	for (int i = 1; i <= AmountOfRaces; i++)
	{
		const float PositionOffset = 162.0f;
		const float Offset = 0.5f;
		URace* NewRace = CreateRace(StartAnchors, TempPosition, StartAlignment);
		if (NewRace)
		{
			NewRace->InitializeWidget(i);
			MatchManager->AddNewRace(NewRace->GetRaceManager());
		}
		TempPosition.Y += PositionOffset;
		if (i % 5 == 0)
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
	MatchManager->OnPopulateRacersRequestDelegate.Broadcast(TeamRosters);
}
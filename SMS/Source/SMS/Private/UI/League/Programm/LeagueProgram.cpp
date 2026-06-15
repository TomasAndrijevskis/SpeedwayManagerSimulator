
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
	if (!MatchManager) return;
	Button_SimulateRace->OnClicked.AddUniqueDynamic(MatchManager, &UMatchManager::SimulateRace);
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
			NewRace->SetRaceID(i);
			MatchManager->AddNewRace(NewRace);
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
	for (const auto& Roster : TeamRosters)
	{
		Roster->TeamManager->ForEachRacer([this](const FString& Name, int Id)
		{
			MatchManager->AssignRacersToRace(Name, Id);
		});
	}
}

/*
void ULeagueProgram::OnRaceFinished(int ID, int NewPoints)
{
	for (const auto& Roster : TeamRosters)
	{
		AddRacerPoints(ID, NewPoints,Roster->GetRacerLines());
	}
}


void ULeagueProgram::AddRacerPoints(int ID, int NewPoints, TArray<URacerStatsLine*>& Racers)
{
	for (auto& Racer : Racers)
	{
		if (Racer->GetID() == ID) Racer->OnValueAddRequestDelegate.Broadcast(FString::FromInt(NewPoints));
	}
}*/
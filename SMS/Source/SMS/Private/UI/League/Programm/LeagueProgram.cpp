
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
#include "SMS/Public/UI/League/Program/RacerStatsLine.h"
#include "SMS/Public/UI/League/Program/TeamRoster.h"


void ULeagueProgram::NativeConstruct()
{
	Super::NativeConstruct();
	Button_ShowTeams->OnClicked.AddUniqueDynamic(this, &ULeagueProgram::ShowTeams);
	CreateTeams();
	CreateRaces();
	BindDelegates();
	ShowTeams();
}


void ULeagueProgram::InitializeMatchManager()
{
	ASMS_GameMode* GameMode = Cast<ASMS_GameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	MatchManager = GameMode->MatchManager;
	if (!MatchManager) return;
	//Button_SimulateRace->OnClicked.AddUniqueDynamic(this, &ULeagueProgram::PrepareToSimulateRace);
}


void ULeagueProgram::CreateTeams()
{
	if (!MatchManager) return; 
	UTeamRoster* HomeTeamRoster = CreateTeam(MatchManager->GetHomeTeamData(), false);
	if (!HomeTeamRoster) return;
	VB_Teams->AddChild(HomeTeamRoster);
	TeamRosters.Add(HomeTeamRoster);
	UTeamRoster* VisitorTeamRoster = CreateTeam(MatchManager->GetVisitorTeamData(), true);
	if (!VisitorTeamRoster) return;
	VB_Teams->AddChild(VisitorTeamRoster);
	TeamRosters.Add(VisitorTeamRoster);
}


UTeamRoster* ULeagueProgram::CreateTeam(const FTeamRosterData* TeamData, bool IsVisitor)
{
	if (!TeamRosterClass) return nullptr;
	UTeamRoster* TeamRoster = CreateWidget<UTeamRoster>(this, TeamRosterClass);
	if (!TeamRoster) return nullptr;
	TeamRoster->SetTeamData(*TeamData);
	TeamRoster->SetIsVisitorTeam(IsVisitor);
	return TeamRoster;
}


void ULeagueProgram::CreateRaces()
{
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
			if (i != 1) NewRace->ChangeRaceStatus(false);
			Races.Add(NewRace);
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
	MatchManager->SetAmountOfRaces(Races.Num());
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


void ULeagueProgram::BindDelegates()
{
	for (const auto& TeamRoster : TeamRosters)
	{
		for (const auto& Racer : TeamRoster->GetRacers())
		{
			Racer->OnRacerChosenDelegate.AddUObject(this, &ULeagueProgram::FillRacers);
		}
	}
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



void ULeagueProgram::FillRacers(FString Name, int Id)
{
	for (const auto& Race : Races)
	{
		Race->AssignRacerToRace(Name, Id);
	}
}


void ULeagueProgram::OnRaceFinished(int ID, int NewPoints)
{
	for (const auto& Roster : TeamRosters)
	{
		AddRacerPoints(ID, NewPoints,Roster->GetRacers());
	}
}


void ULeagueProgram::AddRacerPoints(int ID, int NewPoints, TArray<URacerStatsLine*>& Racers)
{
	for (auto& Racer : Racers)
	{
		if (Racer->GetID() == ID) Racer->OnValueAddRequestDelegate.Broadcast(FString::FromInt(NewPoints));
	}
}
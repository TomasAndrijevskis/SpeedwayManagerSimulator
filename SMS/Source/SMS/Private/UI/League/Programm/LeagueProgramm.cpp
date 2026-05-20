
#include "UI/League/Programm/LeagueProgramm.h"
#include "Components/BackgroundBlur.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/VerticalBox.h"
#include "UI/League/Programm/Race.h"
#include "UI/League/Programm/RacerStatsLine.h"
#include "UI/League/Programm/TeamLineup.h"


void ULeagueProgramm::NativeConstruct()
{
	Super::NativeConstruct();
	Button_SimulateRace->OnClicked.AddUniqueDynamic(this, &ULeagueProgramm::SimulateRace);
	Button_ShowTeams->OnClicked.AddUniqueDynamic(this, &ULeagueProgramm::ShowTeams);
	CreateRaces();
	BindDelegates();
	ShowTeams();
}


void ULeagueProgramm::CreateRaces()
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
}


URace* ULeagueProgramm::CreateRace(const FAnchors& Anchors, const FVector2d& Position, const FVector2d& Alignment)
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


void ULeagueProgramm::BindDelegates()
{
	for (const auto& Racer : TeamLineup_HomeTeam->GetRacers())
	{
		Racer->OnRacerChosenDelegate.AddUObject(this, &ULeagueProgramm::FillRacers);
	}
	for (const auto& Racer : TeamLineup_VisitorTeam->GetRacers())
	{
		Racer->OnRacerChosenDelegate.AddUObject(this, &ULeagueProgramm::FillRacers);
	}
}


void ULeagueProgramm::ShowTeams()
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



void ULeagueProgramm::FillRacers(FString Name, int Id)
{
	for (const auto& Race : Races)
	{
		Race->AssignRacerToRace(Name, Id);
	}
}


void ULeagueProgramm::SimulateRace()
{
	if (CurrentRace < Races.Num())
	{
		Races[CurrentRace]->OnRaceFinishedDelegate.AddUObject(this, &ULeagueProgramm::SetOverallPts);
		Races[CurrentRace]->SimulateRace();
		Races[CurrentRace]->OnRaceFinishedDelegate.Clear();
		CurrentRace++;
	}
}


void ULeagueProgramm::SetOverallPts(int AddHomePts, int AddVisitorPts)
{
	HomeOverallPts += AddHomePts;
	VisitorOverallPts += AddVisitorPts;
	Races[CurrentRace]->UpdateOverallScore(HomeOverallPts, VisitorOverallPts);
}
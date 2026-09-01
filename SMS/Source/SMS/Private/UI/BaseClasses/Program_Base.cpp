
#include "UI/BaseClasses/Program_Base.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"
#include "Gamemodes/SMS_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/MatchManager.h"
#include "UI/League/Program/Race/League_Race.h"
#include "UI/RaceStats/RaceStats.h"


void UProgram::InitializeManagers()
{
	ASMS_GameMode* GameMode = Cast<ASMS_GameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	MatchManager = GameMode->GetMatchManager();
}


void UProgram::BindDelegates()
{
	if (!MatchManager) return;
	Button_ConfirmRacers->OnClicked.AddUniqueDynamic(this, &UProgram::PopulateRacers);
	Button_SimulateRace->OnClicked.AddUniqueDynamic(this, &UProgram::StartRace);
	Button_SimulateMatch->OnClicked.AddUniqueDynamic(this, &UProgram::SimulateMatch);
	MatchManager->OnMatchEndedDelegate.AddUObject(this, &UProgram::PrepareToEndMatch);
}


void UProgram::CreateRaces()
{
	if (!MatchManager) return;
	FVector2d TempPosition = StartPosition;
	FAnchors StartAnchors(0.0f, 0.5f, 0.0f, 0.5f);
	FVector2d StartAlignment = FVector2d(0, 0);
	for (int32 RaceID = 1; RaceID <= AmountOfRaces; RaceID++)
	{
		const float PositionOffset = 162.0f;
		URace_Base* NewRace = CreateRace(StartAnchors, TempPosition, StartAlignment);
		if (NewRace)
		{
			NewRace->InitializeWidget(RaceID, MatchManager->GetScoreManager());
			NewRace->OnRaceStatsUpdateRequestedDelegate.AddUObject(this, &UProgram::OnRaceStatsUpdated);
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


URace_Base* UProgram::CreateRace(const FAnchors& Anchors, const FVector2d& Position, const FVector2d& Alignment)
{
	if (!RaceClass) return nullptr;
	URace_Base* NewRace = CreateWidget<URace_Base>(this, RaceClass);
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


void UProgram::StartRace()
{
	if (!MatchManager) return;
	MatchManager->OnRaceStaredDelegate.Broadcast();
}


void UProgram::SimulateMatch()
{
	if (!MatchManager) return;
	for (int i = 1; i <= MatchManager->GetAmountOfRaces(); i++)
	{
		MatchManager->OnRaceStaredDelegate.Broadcast();
	}
	Button_SimulateMatch->OnClicked.Clear();
}


void UProgram::OnRaceStatsUpdated(const TArray<FRaceResultData>& Data)
{
	if (!RaceStatsWidget) return;
	RaceStatsWidget->UpdateStats(Data);
}


void UProgram::PrepareToEndMatch()
{
	CollectStatistics();
	ChangeButtonBehaviour();
}


void UProgram::ChangeButtonBehaviour()
{
	Text_SimulateButton->SetText(FText::FromString("End match"));
	Button_SimulateRace->OnClicked.Clear();
	Button_SimulateRace->OnClicked.AddUniqueDynamic(this, &UProgram::FinishMatch);
}


void UProgram::CreateRaceStatsWidget()
{
	if (!RaceStatsWidget) return;
	RaceStatsWidget->InitializeWidget();
}


void UProgram::DisableButtons()
{
	Button_ConfirmRacers->SetIsEnabled(false);
}


void UProgram::FinishMatch()
{
	this->RemoveFromParent();
}

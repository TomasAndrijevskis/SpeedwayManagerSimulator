
#include "UI/BaseClasses/Program_Base.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"
#include "Data/RaceData/RacePatternsDataAsset.h"
#include "Rules/LeagueRules.h"
#include "Subsystems/MatchManagerSubsystem.h"
#include "UI/League/Program/Race/League_Race.h"
#include "UI/RaceStats/RaceStats.h"


void UProgram::BindDelegates()
{
	Button_SimulateRace->OnClicked.AddUniqueDynamic(this, &UProgram::StartRace);
	Button_SimulateMatch->OnClicked.AddUniqueDynamic(this, &UProgram::SimulateMatch);
	if (UMatchManagerSubsystem* MatchManagerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMatchManagerSubsystem>())
	{
		MatchManagerSubsystem->GetCompetitionRules()->OnMatchEndedDelegate.AddUObject(this, &UProgram::PrepareToEndMatch);
	}
}


void UProgram::CreateRaces()
{
	if (!RacePatternDataAsset) return;
	FVector2d TempPosition = StartPosition;
	FAnchors StartAnchors(0.0f, 0.5f, 0.0f, 0.5f);
	FVector2d StartAlignment = FVector2d(0, 0);
	for (int32 RaceID = 1; RaceID <= RacePatternDataAsset->RacePatterns.Num(); RaceID++)
	{
		const float PositionOffset = 162.0f;
		URace_Base* NewRace = CreateRace(StartAnchors, TempPosition, StartAlignment);
		if (NewRace)
		{
			if (UMatchManagerSubsystem* MatchManagerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMatchManagerSubsystem>())
			{
				NewRace->InitializeWidget(RaceID, Cast<ULeagueRules>(MatchManagerSubsystem->GetCompetitionRules())->GetScoreManager());
				//!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				NewRace->OnRaceStatsUpdateRequestedDelegate.AddUObject(this, &UProgram::OnRaceStatsUpdated);
				MatchManagerSubsystem->GetCompetitionRules()->AddNewRace(RaceID, NewRace->GetRaceData());
			}
			
		}
		TempPosition.Y += PositionOffset;
		if (RaceID % AmountOfRows == 0)
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
	NewRace->SetRacePatternDataAsset(RacePatternDataAsset);
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
	if (UMatchManagerSubsystem* MatchManagerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMatchManagerSubsystem>())
	{
		MatchManagerSubsystem->GetCompetitionRules()->OnRaceStartedDelegate.Broadcast();
	}
}


void UProgram::SimulateMatch()
{
	if (UMatchManagerSubsystem* MatchManagerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMatchManagerSubsystem>())
	{
		int32 RacesAmount = MatchManagerSubsystem->GetCompetitionRules()->GetAmountOfRaces();
		for (int i = 1; i <= RacesAmount; i++)
		{
			MatchManagerSubsystem->GetCompetitionRules()->OnRaceStartedDelegate.Broadcast();
		}
		Button_SimulateMatch->OnClicked.Clear();
	}
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


void UProgram::FinishMatch()
{
	this->RemoveFromParent();
}

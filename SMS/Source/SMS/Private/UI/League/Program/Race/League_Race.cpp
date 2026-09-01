
#include "SMS/Public/UI/League/Program/Race/League_Race.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Data/RaceData/RacePatternsDataAsset.h"
#include "Managers/RaceLineupManager.h"
#include "Managers/RaceManager.h"
#include "Managers/ScoreManager.h"
#include "UI/League/Program/ScoreCounter.h"
#include "UI/League/Program/Race/NominatedRaceLine.h"
#include "UI/League/Program/Race/RaceLine.h"


void ULeague_Race::InitializeWidget(int32 NewID, UScoreManager* ScoreManagerRef)
{
	ScoreManager = ScoreManagerRef;
	Super::InitializeWidget(NewID, ScoreManagerRef);
}


void ULeague_Race::InitializeRaceData()
{
	Super::InitializeRaceData();
	FRaceData data;
	data.RaceManager = NewObject<URaceManager>(this);
	data.RaceLineupManager = NewObject<URaceLineupManager>(this);
	if (!data.RaceManager || !data.RaceLineupManager) return;
	data.RaceManager->InitializeManager(IsNominatedRace());
	data.RaceLineupManager->InitializeManager();
	Data = data;
}


void ULeague_Race::BindDelegates()
{
	Super::BindDelegates();
	if (!Data.RaceManager) return;
	Data.RaceManager->OnRaceFinishedDelegate.AddUObject(this, &ULeague_Race::UpdateRacePoints);
	Data.RaceManager->OnRaceFinishedDelegate.AddUObject(this, &ULeague_Race::UpdateOverallScore);
	Data.RaceManager->OnRaceLineResultUpdatedDelegate.AddUObject(this, &URace_Base::OnRaceStatsUpdateRequested);
}


void ULeague_Race::CreateRaceLines()
{
	if (!Data.RaceManager || !Data.RaceLineupManager || !RacePatternDataAsset) return;
	const int32 RaceLineAmount = RacePatternDataAsset->RacePatterns[RaceID].RaceLines.Num();
	for (int32 RaceLineID = 0; RaceLineID < RaceLineAmount; RaceLineID++)
	{
		ULeague_RaceLine_Base* NewRaceLine;
		if (!IsNominatedRace()) NewRaceLine = CreateRaceLine(RaceLineID);
		else NewRaceLine = CreateNominatedRaceLine(RaceLineID);
		if (NewRaceLine)
		{
			UVerticalBoxSlot* VB_Slot = VB_Content->AddChildToVerticalBox(NewRaceLine);
			if (VB_Slot)
			{
				VB_Slot->SetHorizontalAlignment(HAlign_Fill);
				VB_Slot->SetVerticalAlignment(VAlign_Fill);
			}
			
			NewRaceLine->SetRaceLineData(GetRaceLineData(RaceLineID));
			Data.RaceManager->AddRaceLine(NewRaceLine);
			Data.RaceLineupManager->AddRaceLine(NewRaceLine);
		}
	}
	Data.RaceLineupManager->OnRaceInitialized();
}


ULeague_RaceLine_Base* ULeague_Race::CreateRaceLine(int32 RaceLineID)
{
	if (!RaceLineClass) return nullptr;
	ULeague_RaceLine_Base* NewRaceLine = CreateWidget<ULeague_RaceLine_Base>(this, RaceLineClass);
	if (!NewRaceLine) return nullptr;
	NewRaceLine->SetRaceLineID(RaceLineID);
	return NewRaceLine;
}


ULeague_RaceLine_Base* ULeague_Race::CreateNominatedRaceLine(int32 RaceLineID)
{
	if (!NominatedRaceLineClass) return nullptr;
	UNominatedRaceLine* NewRaceLine = CreateWidget<UNominatedRaceLine>(this, NominatedRaceLineClass);
	if (!NewRaceLine) return nullptr;
	NewRaceLine->SetRaceLineID(RaceLineID);
	return NewRaceLine;
}


void ULeague_Race::UpdateRacePoints()
{
	if (!ScoreManager) return;
	ScoreCounter->SetRacePoints(
		ScoreManager->GetRaceScore(false),
		ScoreManager->GetRaceScore(true));
}


void ULeague_Race::UpdateOverallScore()
{
	if (!ScoreManager) return;
	ScoreCounter->SetOverallScore(
		ScoreManager->GetTeamScore(false),
		ScoreManager->GetTeamScore(true));
}

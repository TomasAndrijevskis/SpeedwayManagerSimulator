
#include "SMS/Public/UI/League/Program/Race/LeagueRace.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Data/RaceData/RacePatternsDataAsset.h"
#include "Managers/RaceLineupManager.h"
#include "Managers/RaceManager.h"
#include "Managers/ScoreManager.h"
#include "UI/League/Program/ScoreCounter.h"
#include "UI/League/Program/Race/NominatedRaceLine.h"
#include "UI/League/Program/Race/RaceLine.h"
#include "UI/League/Program/Race/RaceLineBase.h"


void ULeagueRace::InitializeWidget(int32 NewID, UScoreManager* ScoreManagerRef)
{
	Super::InitializeWidget(NewID, ScoreManagerRef);
	ScoreManager = ScoreManagerRef;
}


void ULeagueRace::InitializeRaceData()
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


void ULeagueRace::BindDelegates()
{
	Super::BindDelegates();
	if (!Data.RaceManager) return;
	Data.RaceManager->OnRaceFinishedDelegate.AddUObject(this, &ULeagueRace::UpdateRacePoints);
	Data.RaceManager->OnRaceFinishedDelegate.AddUObject(this, &ULeagueRace::UpdateOverallScore);
	Data.RaceManager->OnRaceLineResultUpdatedDelegate.AddUObject(this, &URace_Base::OnRaceStatsUpdateRequested);
}



void ULeagueRace::CreateRaceLines()
{
	if (!Data.RaceManager || !Data.RaceLineupManager || !RacePatternDataAsset) return;
	const int32 RaceLineAmount = RacePatternDataAsset->RacePatterns[RaceID].RaceLines.Num();
	for (int32 RaceLineID = 0; RaceLineID < RaceLineAmount; RaceLineID++)
	{
		URaceLineBase* NewRaceLine;
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


URaceLineBase* ULeagueRace::CreateRaceLine(int32 RaceLineID)
{
	if (!RaceLineClass) return nullptr;
	URaceLine* NewRaceLine = CreateWidget<URaceLine>(this, RaceLineClass);
	if (!NewRaceLine) return nullptr;
	NewRaceLine->SetRaceLineID(RaceLineID);
	return NewRaceLine;
}


URaceLineBase* ULeagueRace::CreateNominatedRaceLine(int32 RaceLineID)
{
	if (!NominatedRaceLineClass) return nullptr;
	UNominatedRaceLine* NewRaceLine = CreateWidget<UNominatedRaceLine>(this, NominatedRaceLineClass);
	if (!NewRaceLine) return nullptr;
	NewRaceLine->SetRaceLineID(RaceLineID);
	return NewRaceLine;
}


void ULeagueRace::UpdateRacePoints()
{
	if (!ScoreManager) return;
	ScoreCounter->SetRacePoints(
		ScoreManager->GetRaceScore(false),
		ScoreManager->GetRaceScore(true));
}


void ULeagueRace::UpdateOverallScore()
{
	if (!ScoreManager) return;
	ScoreCounter->SetOverallScore(
		ScoreManager->GetTeamScore(false),
		ScoreManager->GetTeamScore(true));
}



bool ULeagueRace::IsNominatedRace() const{return RacePatternDataAsset->RacePatterns[RaceID].IsNominatedRace;}

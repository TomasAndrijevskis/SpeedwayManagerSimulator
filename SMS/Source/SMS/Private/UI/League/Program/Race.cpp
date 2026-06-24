
#include "SMS/Public/UI/League/Program/Race.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Data/RaceData/RacePatternsDataAsset.h"
#include "Managers/RaceManager.h"
#include "UI/BaseClasses/NumbersBox.h"
#include "SMS/Public/UI/League/Program/RaceLine.h"
#include "SMS/Public/UI/League/Program/ScoreCounter.h"


void URace::NativeConstruct()
{
	Super::NativeConstruct();
	InitializeManagers();
	BindDelegates();
}


void URace::InitializeWidget(int NewID)
{
	RaceID = NewID;
	NumbersBox_RaceNumber->SetText(RaceID);
	OnIDSet();
}


void URace::OnIDSet()
{
	CreateRaceLines();
	if (RaceID != 1) RaceManager->ChangeRaceStatus(false);
}


void URace::InitializeManagers()
{
	RaceManager = NewObject<URaceManager>(this);
	if (!RaceManager) return;
	RaceManager->BindDelegates();
}


void URace::BindDelegates()
{
	if (!RaceManager) return;
	RaceManager->OnRaceScoreUpdatedDelegate.AddUObject(this, &URace::UpdateRaceScore);
	RaceManager->OnOverallScoreUpdatedDelegate.AddUObject(this, &URace::UpdateOverallScore);
}


void URace::CreateRaceLines()
{
	if (!RaceManager || !RaceDataAsset) return;
	for (int RaceLineID = 0; RaceLineID < RaceLineAmount; RaceLineID++)
	{
		URaceLine* NewRaceLine = CreateRaceLine(RaceLineID);
		if (NewRaceLine)
		{
			UVerticalBoxSlot* VB_Slot = VB_Content->AddChildToVerticalBox(NewRaceLine);
			if (VB_Slot)
			{
				VB_Slot->SetHorizontalAlignment(HAlign_Fill);
				VB_Slot->SetVerticalAlignment(VAlign_Fill);
			}
			NewRaceLine->SetRaceLineData(
				GetRequiredHelmetColor(RaceID, RaceLineID),
				GetRacerId(RaceID, RaceLineID));
			RaceManager->AddRaceLine(NewRaceLine);
		}
	}
}


URaceLine* URace::CreateRaceLine(int RaceLineID)
{
	if (!RaceLineClass) return nullptr;
	URaceLine* NewRaceLine = CreateWidget<URaceLine>(this, RaceLineClass);
	if (!NewRaceLine) return nullptr;
	NewRaceLine->SetRaceLineID(RaceLineID);
	return NewRaceLine;
}


void URace::UpdateOverallScore(int NewHomePts, int NewVisitorPts)
{
	ScoreCounter->SetOverallScore(NewHomePts, NewVisitorPts);
}


void URace::UpdateRaceScore(int NewHomePts, int NewVisitorPts)
{
	ScoreCounter->SetRacePoints(NewHomePts, NewVisitorPts);
}


const FColor& URace::GetRequiredHelmetColor(int RaceId, int RaceLineId) const{return RaceDataAsset->RacePatterns[RaceId].HelmetColors[RaceLineId];}
int URace::GetRacerId(int RaceId, int RaceLineId) const{return RaceDataAsset->RacePatterns[RaceId].RacerIDs[RaceLineId];}
URaceManager* URace::GetRaceManager() const{return RaceManager;}

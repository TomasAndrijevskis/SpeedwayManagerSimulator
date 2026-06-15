
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


void URace::InitializeManagers()
{
	RaceManager = NewObject<URaceManager>(this);
}


void URace::BindDelegates()
{
	if (!RaceManager) return;
	OnAssignRacerRequestDelegate.AddUObject(RaceManager, &URaceManager::AssignRacerToRace);
	OnSimulateRaceRequestDelegate.AddUObject(RaceManager, &URaceManager::SimulateRace);
	OnRaceStatusChangedDelegate.AddUObject(RaceManager, &URaceManager::ChangeRaceStatus);
}


void URace::SetRaceID(int NewID)
{
	ID = NewID;
	NumbersBox_RaceNumber->SetText(ID);
	OnIDSet();
}


void URace::OnIDSet()
{
	CreateRaceLines();
	if (ID != 1) RaceManager->ChangeRaceStatus(false);
}


void URace::CreateRaceLines()
{
	if (!RaceManager) return;
	for (int i = 0; i < RaceLineAmount; i++)
	{
		URaceLine* NewRaceLine = CreateRaceLine(i);
		if (NewRaceLine)
		{
			UVerticalBoxSlot* VB_Slot = VB_Content->AddChildToVerticalBox(NewRaceLine);
			if (VB_Slot)
			{
				VB_Slot->SetHorizontalAlignment(HAlign_Fill);
				VB_Slot->SetVerticalAlignment(VAlign_Fill);
			}
			RaceManager->AddRaceLine(NewRaceLine);
		}
	}
	SetRaceData();
}


URaceLine* URace::CreateRaceLine(int RaceLineID)
{
	if (!RaceLineClass) return nullptr;
	URaceLine* NewRaceLine = CreateWidget<URaceLine>(this, RaceLineClass);
	if (!NewRaceLine) return nullptr;
	NewRaceLine->SetRaceLineID(RaceLineID);
	return NewRaceLine;
}


void URace::SetRaceData()
{
	if (!RaceDataAsset) return;
	for (auto& RaceLine : RaceManager->GetRaceLines())
	{
		RaceLine->SetRacerValues(
			RaceDataAsset->RacePatterns[ID].HelmetColors[RaceLine->GetRaceLineID()],
			RaceDataAsset->RacePatterns[ID].RacerIDs[RaceLine->GetRaceLineID()]);
	}
}


void URace::UpdateOverallScore(int NewHomePts, int NewVisitorPts)
{
	ScoreCounter->SetOverallScore(NewHomePts, NewVisitorPts);
}
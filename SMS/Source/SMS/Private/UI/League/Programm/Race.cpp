
#include "SMS/Public/UI/League/Program/Race.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Data/RaceData/RacePatternsDataAsset.h"
#include "UI/BaseClasses/NumbersBox.h"
#include "SMS/Public/UI/League/Program/RaceLine.h"
#include "SMS/Public/UI/League/Program/ScoreCounter.h"


void URace::SetRaceID(int NewID)
{
	ID = NewID;
	NumbersBox_RaceNumber->SetText(ID);
	CreateRaceLines();
}


void URace::CreateRaceLines()
{
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
			RaceLines.Add(NewRaceLine);
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
	for (auto& RaceLine : RaceLines)
	{
		RaceLine->SetRacerValues(
			RaceDataAsset->RacePatterns[ID].HelmetColors[RaceLine->GetRaceLineID()],
			RaceDataAsset->RacePatterns[ID].RacerIDs[RaceLine->GetRaceLineID()]);
	}
}


void URace::AssignRacerToRace(FString RacerName, int RacerID)
{
	for (const auto& RaceLine : RaceLines)
	{
		if (RaceLine->GetRacerID() == RacerID)
		{
			RaceLine->SetRacerName(RacerName);
		}
	}
}


void URace::SimulateRace()
{
	SortArray();
	int Points = 0;
	for (const auto& RaceLine : RaceLines)
	{
		RaceLine->SetPoints(Points);
		OnRaceFinishedDelegate.Broadcast(RaceLine->GetRacerID(),Points);
		Points++;
	}
	ChangeRaceStatus(false);
	CalculateRaceResult();
}


void URace::ChangeRaceStatus(bool bIsActive)
{
	for (auto& RaceLine : RaceLines)
	{
		RaceLine->SetIsEnabled(bIsActive);
	}
}


void URace::CalculateRaceResult()
{
	int HomePts = 0;
	int VisitorPts = 0;
	for (auto& RaceLine : RaceLines)
	{
		if (RaceLine->GetIsVisitor())  VisitorPts += RaceLine->GetPoints();
		else HomePts += RaceLine->GetPoints();
	}
	ScoreCounter->SetRacePoints(HomePts, VisitorPts);
	OnOverallScoreUpdatedDelegate.Broadcast(HomePts, VisitorPts);
}


void URace::UpdateOverallScore(int NewHomePts, int NewVisitorPts)
{
	ScoreCounter->SetOverallScore(NewHomePts, NewVisitorPts);
}


void URace::SortArray()
{
	RaceLines.Sort([](URaceLine& L1, URaceLine& L2)
	{
		return L1.GetGeneratedNumber() < L2.GetGeneratedNumber();
	});
}

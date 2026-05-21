
#include "UI/League/Programm/Race.h"
#include "Data/RaceDataAsset.h"
#include "UI/BaseClasses/NumbersBox.h"
#include "UI/League/Programm/RaceLine.h"
#include "UI/League/Programm/ScoreCounter.h"


void URace::NativeConstruct()
{
	Super::NativeConstruct();
	RaceLines.Add(RaceLine_First);
	RaceLines.Add(RaceLine_Second);
	RaceLines.Add(RaceLine_Third);
	RaceLines.Add(RaceLine_Fourth);
}


void URace::SetRaceID(int NewID)
{
	ID = NewID;
	NumbersBox_RaceNumber->SetText(ID);
	SetRaceLinesID();
}


void URace::SetRaceLinesID()
{
	int RaceLineID = 0;
	for (auto& RaceLine : RaceLines)
	{
		RaceLine->SetRacerLineID(RaceLineID);
		RaceLineID++;
	}
	SetRaceData();
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
	CalculateRaceResult();
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

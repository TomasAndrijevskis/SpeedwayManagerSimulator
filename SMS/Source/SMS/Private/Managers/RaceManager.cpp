
#include "Managers/RaceManager.h"


void URaceManager::SimulateRace()
{
	UE_LOG(LogTemp, Error, TEXT("Simulate race"));
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


void URaceManager::ChangeRaceStatus(bool bIsActive)
{
	for (auto& RaceLine : RaceLines)
	{
		RaceLine->SetIsEnabled(bIsActive);
	}
}


void URaceManager::CalculateRaceResult()
{
	int HomePts = 0;
	int VisitorPts = 0;
	for (auto& RaceLine : RaceLines)
	{
		if (RaceLine->GetIsVisitor())  VisitorPts += RaceLine->GetPoints();
		else HomePts += RaceLine->GetPoints();
	}
	OnOverallScoreUpdatedDelegate.Broadcast(HomePts, VisitorPts);
}


void URaceManager::SortArray()
{
	RaceLines.Sort([](URaceLine& L1, URaceLine& L2)
	{
		return L1.GetGeneratedNumber() < L2.GetGeneratedNumber();
	});
}


void URaceManager::AddRaceLine(URaceLine* NewRaceLine)
{
	RaceLines.Add(NewRaceLine);
}


void URaceManager::AssignRacerToRace(const FString& RacerName, int RacerID)
{
	for (const auto& RaceLine : RaceLines)
	{
		if (RaceLine->GetRacerID() == RacerID) RaceLine->SetRacerName(RacerName);
	}
}


TArray<URaceLine*> URaceManager::GetRaceLines(){return RaceLines;}
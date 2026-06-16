
#include "Managers/RaceManager.h"


void URaceManager::SimulateRace()
{
	SortArray();
	int Points = 0;
	for (const auto& RaceLine : RaceLines)
	{
		RaceLine->SetPoints(Points);
		//OnRaceFinishedDelegate.Broadcast(RaceLine->GetRacerID(),Points);
		Points++;
	}
	OnRaceFinishedDelegate.Broadcast();
}


void URaceManager::ChangeRaceStatus(bool bIsActive)
{
	for (auto& RaceLine : RaceLines)
	{
		RaceLine->SetIsEnabled(bIsActive);
	}
}


void URaceManager::CalculateRaceResult(int& HomePts, int& VisitorPts)
{
	for (auto& RaceLine : RaceLines)
	{
		if (RaceLine->GetIsVisitor())  VisitorPts += RaceLine->GetPoints();
		else HomePts += RaceLine->GetPoints();
	}
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
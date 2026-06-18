
#include "Managers/RaceManager.h"


void URaceManager::SimulateRace()
{
	for (const auto& RaceLine : RaceLines)
	{
		RaceLine->CalculateRating();
	}
	SortArray();
	int Points = 0;
	for (const auto& RaceLine : RaceLines)
	{
		RaceLine->SetPointsPerRace(Points);
		RaceLine->OnRaceFinished();
		//OnRaceFinishedDelegate.Broadcast(RaceLine->GetRacerID(),Points);
		Points++;
	}
	OnRaceFinishedDelegate.Broadcast();
	UE_LOG(LogTemp, Error, TEXT("---------"));
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
	for (const auto& RaceLine : RaceLines)
	{
		if (RaceLine->GetIsVisitor())
		{
			UE_LOG(LogTemp, Display, TEXT("Is visitor: %i"), RaceLine->GetRacerID());
			VisitorPts += RaceLine->GetPointsPerRace();
		}
		else HomePts += RaceLine->GetPointsPerRace();
	}
	UE_LOG(LogTemp, Error, TEXT("Result: %i, %i"), HomePts, VisitorPts);
}


void URaceManager::SortArray()
{
	RaceLines.Sort([](URaceLine& L1, URaceLine& L2)
	{
		return L1.GetRacerRating() < L2.GetRacerRating();
	});
}


void URaceManager::AddRaceLine(URaceLine* NewRaceLine)
{
	RaceLines.Add(NewRaceLine);
}


void URaceManager::AssignRacerToRace(const FRacerData& RacerData, int RacerID)
{
	for (const auto& RaceLine : RaceLines)
	{
		if (RaceLine->GetRacerID() == RacerID) RaceLine->SetRacerData(RacerData);
	}
}


TArray<URaceLine*> URaceManager::GetRaceLines(){return RaceLines;}
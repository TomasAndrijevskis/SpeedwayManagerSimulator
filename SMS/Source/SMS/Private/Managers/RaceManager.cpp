
#include "Managers/RaceManager.h"


void URaceManager::SimulateRace()
{
	for (const auto& RaceLine : RaceLines)
	{
		RaceLine->OnRaceStartedDelegate.Broadcast();
	}
	SortLinesByRating();
	int Points = 0;
	for (const auto& RaceLine : RaceLines)
	{
		RaceLine->SetPointsPerRace(Points);
		RaceLine->OnRaceFinished();
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
		if (RaceLine->IsVisitor())
		{
			VisitorPts += RaceLine->GetPointsPerRace();
		}
		else HomePts += RaceLine->GetPointsPerRace();
	}
}


void URaceManager::SortLinesByRating()
{
	RaceLines.Sort([](const URaceLine& L1, const URaceLine& L2)
	{
		if (L1.GetRacerRating() == L2.GetRacerRating())
		{
			UE_LOG(LogTemp, Error, TEXT("!!!!!!!!!!!!Same rating!!!!!!!!!!!!!"));
			return L1.GetTieBreaker() < L2.GetTieBreaker();
		}
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
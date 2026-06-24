
#include "Managers/RaceManager.h"


void URaceManager::BindDelegates()
{
	OnRaceStatusChangedDelegate.AddUObject(this, &URaceManager::ChangeRaceStatus);
	OnSimulateRaceRequestDelegate.AddUObject(this, &URaceManager::SimulateRace);
}


void URaceManager::UpdateOverallScore(int HomePts, int VisitorPts)
{
	OnOverallScoreUpdatedDelegate.Broadcast(HomePts, VisitorPts);
}


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
	CalculateRaceResult();
	UE_LOG(LogTemp, Error, TEXT("---------"));
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
	for (const auto& RaceLine : RaceLines)
	{
		if (RaceLine->IsVisitor())
		{
			VisitorPts += RaceLine->GetPointsPerRace();
		}
		else HomePts += RaceLine->GetPointsPerRace();
	}
	OnRaceScoreUpdatedDelegate.Broadcast(HomePts, VisitorPts);
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
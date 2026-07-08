
#include "Managers/RaceManager.h"
#include "Data/RacersData/RacerMatchData.h"


void URaceManager::BindDelegates()
{
	OnRaceStatusChangedDelegate.AddUObject(this, &URaceManager::ChangeRaceStatus);
	OnRaceSimulationStartedDelegate.AddUObject(this, &URaceManager::SimulateRace);
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
	for (int Position = 0, Points = 3; Position < RaceLines.Num(); Position++, Points--)
	{
		URaceLineBase* CurrentLine = RaceLines[Position];
		const bool IsVisitor = CurrentLine->IsVisitor();
		bool HasBonus = false;
		if (Position != 0 && Position < RaceLines.Num() - 1)
			HasBonus = RaceLines[Position - 1]->IsVisitor() == IsVisitor;
		if (CurrentLine->GetRacerRating() == 0)
			CurrentLine->SetPointsPerRace(DidNotFinish, false);
		else
			CurrentLine->SetPointsPerRace(FString::FromInt(Points), HasBonus);
	}
	CalculateRaceResult();
	UE_LOG(LogTemp, Error, TEXT("---------"));
}


void URaceManager::ChangeRaceStatus(bool bIsActive)
{
	for (auto& RaceLine : RaceLines)
	{
		RaceLine->HandleRace(bIsActive);
	}
}


void URaceManager::CalculateRaceResult()
{
	//int HomePts = 0;
	//int VisitorPts = 0;
	for (const auto& RaceLine : RaceLines)
	{
		//if (RaceLine->IsVisitor()) VisitorPts += RaceLine->GetPointsPerRace();
		//else HomePts += RaceLine->GetPointsPerRace();
		OnRaceScoreUpdatedDelegate.Broadcast(RaceLine->GetTeamID(), RaceLine->GetPointsPerRace());
	}
}


void URaceManager::SortLinesByRating()
{
	RaceLines.Sort([](const URaceLineBase& L1, const URaceLineBase& L2)
	{
		if (L1.GetRacerRating() == L2.GetRacerRating())
		{
			//UE_LOG(LogTemp, Error, TEXT("!!!!!!!!!!!!Same rating!!!!!!!!!!!!!"));
			return L1.GetTieBreaker() > L2.GetTieBreaker();
		}
		return L1.GetRacerRating() > L2.GetRacerRating();
	});
}


void URaceManager::AddRaceLine(URaceLineBase* NewRaceLine)
{
	RaceLines.Add(NewRaceLine);
}


void URaceManager::AssignRacerToRace(const FRacerMatchData& RacerData, URacerManager* RacerManagerRef)
{
	for (const auto& RaceLine : RaceLines)
	{
		if (RaceLine->GetRacerNumber() == RacerData.RacerNumber) RaceLine->SetRacerData(RacerData, RacerManagerRef);
	}
}


TArray<URaceLineBase*> URaceManager::GetRaceLines(){return RaceLines;}
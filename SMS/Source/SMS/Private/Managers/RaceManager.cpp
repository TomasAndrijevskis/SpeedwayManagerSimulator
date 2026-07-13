
#include "Managers/RaceManager.h"
#include "Managers/RaceLineupManager.h"


void URaceManager::InitializeManager()
{
	BindDelegates();
	RaceLineupManager = NewObject<URaceLineupManager>(this);
	if (!RaceLineupManager) return;
	RaceLineupManager->InitializeManager();
}


void URaceManager::BindDelegates()
{
	OnChangedRaceStatusRequestDelegate.AddUObject(this, &URaceManager::ChangeRaceStatus);
	OnSimulateRaceRequestDelegate.AddUObject(this, &URaceManager::SimulateRace);
}


void URaceManager::AddRaceLine(URaceLineBase* NewRaceLine)
{
	RaceLines.Add(NewRaceLine);
}


void URaceManager::OnRaceLinesCreated() const
{
	if (!RaceLineupManager) return;
	RaceLineupManager->SetRaceLines(RaceLines);
}


void URaceManager::ChangeRaceStatus(bool bIsActive)
{
	for (auto& RaceLine : RaceLines)
	{
		RaceLine->ChangeLineStatus(bIsActive);
		RaceLine->HandleRaceLine(RaceLineupManager->IsTeamLosing(RaceLine));
	}
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
	UE_LOG(LogTemp, Error, TEXT("==================================="));
	BroadcastRaceResult();
	OnRaceFinished();
}


void URaceManager::BroadcastRaceResult()
{
	for (const auto& RaceLine : RaceLines)
	{
		OnRaceScoreUpdatedDelegate.Broadcast(RaceLine->GetTeamID(), RaceLine->GetPointsPerRace());
	}
}


void URaceManager::OnRaceFinished()
{
	OnRaceFinishedDelegate.Broadcast();
	OnChangedRaceStatusRequestDelegate.Broadcast(false);
	OnRaceScoreUpdatedDelegate.Clear();
}


void URaceManager::SortLinesByRating()
{
	RaceLines.Sort([](const URaceLineBase& L1, const URaceLineBase& L2)
	{
		if (L1.GetRacerRating() == L2.GetRacerRating())
		{
			return L1.GetTieBreaker() > L2.GetTieBreaker();
		}
		return L1.GetRacerRating() > L2.GetRacerRating();
	});
}


TArray<URaceLineBase*> URaceManager::GetRaceLines(){return RaceLines;}
URaceLineupManager* URaceManager::GetRaceLineupManager() const{return RaceLineupManager;}

#include "Managers/RaceManager.h"

#include "Subsystems/RulesSubsystem.h"
#include "UI/League/Program/Race/RaceLineBase.h"


void URaceManager::InitializeManager(bool NewIsNominatedRace)
{
	BindDelegates();
	bIsNominatedRace = NewIsNominatedRace;
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


void URaceManager::ChangeRaceStatus(bool bIsActive)
{
	for (auto& RaceLine : RaceLines)
	{
		RaceLine->ChangeLineStatus(bIsActive);
	}
}


void URaceManager::SimulateRace()
{
	if (URulesSubsystem* Rules = GetWorld()->GetGameInstance()->GetSubsystem<URulesSubsystem>())
	{
		for (const auto& RaceLine : RaceLines)
		{
			RaceLine->OnRaceStartedDelegate.Broadcast();
		}
		SortLinesByRating();
		for (int32 Position = 0; Position < RaceLines.Num(); Position++)
		{
			ERaceResults Result = static_cast<ERaceResults>(Position);
			URaceLineBase* CurrentLine = RaceLines[Position];
			const bool IsVisitor = CurrentLine->GetRaceLineData().IsVisitorLine();
			bool HasBonus = false;
			if (Position != 0 && Position < RaceLines.Num() - 1)
				HasBonus = RaceLines[Position - 1]->GetRaceLineData().IsVisitorLine() == IsVisitor;
			if (CurrentLine->GetRacerRating() == 0)
				CurrentLine->SetPointsPerRace(Rules->GetRaceResultText(ERaceResults::Defect), false);
			else
				CurrentLine->SetPointsPerRace(Rules->GetRaceResultText(Result), HasBonus);
			FRaceResultData Data;
			Data.RacerScore = Rules->GetRaceResultNumber(Result);
			Data.RaceLineID = CurrentLine->GetRaceLineID();
			RaceResults.Add(Data);
		}
		UE_LOG(LogTemp, Error, TEXT("==================================="));
		OnRaceLineResultUpdatedDelegate.Broadcast(RaceResults);
		BroadcastRaceResult();
		OnRaceFinished();
	}
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
	OnRaceLineResultUpdatedDelegate.Clear();
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


bool URaceManager::CheckAllRacersInRace() const
{
	for (const auto& RaceLine : RaceLines)
	{
		if (!RaceLine->IsRacerSet()) return false;
	}
	return true;
}


bool URaceManager::IsNominatedRace()const{return bIsNominatedRace;}

#include "Managers/RaceManager.h"
#include "Managers/RacerMatchManager.h"
#include "Managers/TrackManager.h"
#include "Rules/LeagueRules.h"
#include "Subsystems/MatchManagerSubsystem.h"
#include "Subsystems/RulesSubsystem.h"
#include "UI/League/Program/Race/League_RaceLine_Base.h"


void URaceManager::InitializeManager(bool NewIsNominatedRace, int32 NewRaceID)
{
	BindDelegates();
	bIsNominatedRace = NewIsNominatedRace;
	RaceID = NewRaceID;
}


void URaceManager::InitializeManager()
{
	BindDelegates();
}


void URaceManager::BindDelegates()
{
	OnChangedRaceStatusRequestDelegate.AddUObject(this, &URaceManager::ChangeRaceStatus);
	OnSimulateRaceRequestDelegate.AddUObject(this, &URaceManager::SimulateRace);
}


void URaceManager::AddRaceLine(ULeague_RaceLine_Base* NewRaceLine)
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


void URaceManager::SimulateRace(const TObjectPtr<UTrackManager>& TrackManager)
{
	if (URulesSubsystem* Rules = GetWorld()->GetGameInstance()->GetSubsystem<URulesSubsystem>())
	{
		for (const auto& RaceLine : RaceLines)
		{
			const float StartModifier = TrackManager->GetGateModifier(RaceLine->GetRaceLineID());
			const float DrivingModifier = TrackManager->GetDrivingModifier();
			RaceLine->OnRaceSimulatedDelegate.Broadcast(StartModifier, DrivingModifier, TrackManager->GetCurrentTrackType());
		}
		SortLinesByRating();
		for (int32 Position = 0; Position < RaceLines.Num(); Position++)
		{
			ERaceResults Result = static_cast<ERaceResults>(Position);
			ULeague_RaceLine_Base* CurrentLine = RaceLines[Position];
			const bool IsVisitor = CurrentLine->IsVisitor();
			bool HasBonus = false;
			if (Position != 0 && Position < RaceLines.Num() - 1)
				HasBonus = RaceLines[Position - 1]->IsVisitor() == IsVisitor;
			if (CurrentLine->GetRacerRating() == 0)
			{
				CurrentLine->SetPointsPerRace(Rules->GetRaceResultText(ERaceResults::Defect));
				CurrentLine->GetRacerManager()->AddPoints(ERaceResults::Defect, false);
			}
			else
			{
				CurrentLine->SetPointsPerRace(Rules->GetRaceResultText(Result));
				CurrentLine->GetRacerManager()->AddPoints(Result, HasBonus);
			}
			
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
	if (UMatchManagerSubsystem* MatchManagerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMatchManagerSubsystem>())
	{
		for (const auto& RaceLine : RaceLines)
		{
			if (ULeagueRules* Rules = Cast<ULeagueRules>(MatchManagerSubsystem->GetCompetitionRules()))
			{
				Rules->OnScoreUpdatedDelegate.Broadcast(RaceLine->IsVisitor(), RaceLine->GetPointsPerRace(), RaceID);
			}
		}
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
	RaceLines.Sort([](const URaceLine_Base& L1, const URaceLine_Base& L2)
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
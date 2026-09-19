
#include "Managers/RaceManagers/RaceManager_Base.h"
#include "Managers/RacerMatchManager.h"
#include "Managers/TrackManager.h"
#include "Subsystems/MatchManagerSubsystem.h"


void URaceManager_Base::InitializeManager(bool NewIsNominatedRace, int32 NewRaceID)
{
	BindDelegates();
	bIsNominatedRace = NewIsNominatedRace;
	RaceID = NewRaceID;
}


void URaceManager_Base::BindDelegates()
{
	OnSimulateRaceDelegate.AddUObject(this, &URaceManager_Base::SimulateRace);
}


void URaceManager_Base::AddRacerManager(URacerMatchManager* NewRacerMatchManager, int32 RaceLineID)
{
	if (NewRacerMatchManager && !Racers.Contains(RaceLineID))
		Racers.Add(RaceLineID, NewRacerMatchManager);
}


void URaceManager_Base::ApplyRacerResult(URacerMatchManager& Racer, ERaceResults& Result, bool HasBonus)
{
	if (Racer.GetCurrentRaceRating() == 0)
	{
		Racer.AddPoints(ERaceResults::Defect, false);
		Result = ERaceResults::Defect;
	}
	else Racer.AddPoints(Result, HasBonus);
}


void URaceManager_Base::CalculateRacerRatings()
{
	if (UMatchManagerSubsystem* MatchManagerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMatchManagerSubsystem>())
	{
		if (UTrackManager* TrackManager = MatchManagerSubsystem->GetCompetitionRules()->GetTrackManager())
		{
			for (const auto& Racer : Racers)
			{
				const float StartModifier = TrackManager->GetGateModifier(Racer.Key);
				const float DrivingModifier = TrackManager->GetDrivingModifier();
				Racer.Value->CalculateRating(StartModifier, DrivingModifier, TrackManager->GetCurrentTrackType());
			}
		}
	}
}


void URaceManager_Base::CollectRaceResults(ERaceResults Result, int32 RaceLineID, const UCompetitionRules& Rules)
{
	FRaceResultData Data;
	Data.Points = Rules.GetRaceResultAsNumber(Result);
	Data.RacerNumber = RaceLineID;
	RaceResults.Add(Data);
}


void URaceManager_Base::OnRaceFinished()
{
	OnRaceLineResultUpdatedDelegate.Clear();
	OnRaceFinishedDelegate.Broadcast();
	OnChangedRaceStatusDelegate.Broadcast(false);
	OnRaceScoreUpdatedDelegate.Clear();
}


void URaceManager_Base::SortLinesByRating()
{
	TArray<TPair<int32, URacerMatchManager*>> SortedRacers;
	for (const auto& Racer : Racers)
	{
		SortedRacers.Add(Racer);
	}
	
	SortedRacers.Sort([](const auto& L1, const auto& L2)
	{
		URacerMatchManager* MatchManager1 = L1.Value;
		URacerMatchManager* MatchManager2 = L2.Value;
		if (MatchManager1->GetCurrentRaceRating() == MatchManager2->GetCurrentRaceRating())
		{
			return MatchManager1->GetTieBreaker() > MatchManager2->GetTieBreaker();
		}
		return MatchManager1->GetCurrentRaceRating() > MatchManager2->GetCurrentRaceRating();
	});
	Racers.Empty();
	for (const auto& SortedRacer : SortedRacers)
	{
		Racers.Add(SortedRacer.Key, SortedRacer.Value);
	}
}


bool URaceManager_Base::AreAllRacersSet()
{
	if (Racers.Num() < 4) return false;
	return true;
}


FString URaceManager_Base::GetRaceLinePoints(int32 RaceLineID)
{
	if (UMatchManagerSubsystem* MatchManagerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMatchManagerSubsystem>())
	{
		if (UCompetitionRules* Rules = MatchManagerSubsystem->GetCompetitionRules())
		{
			for (const auto& Racer : Racers)
			{
				if (Racer.Key == RaceLineID)
				{
					return Rules->GetRaceResultText(Racer.Value->GetLastRaceResult());
				}
			}
		}
	}
	return "";
}



#include "Managers/RaceManager.h"

#include "Data/RaceData/RaceLineResultData.h"
#include "Managers/RacerMatchManager.h"
#include "Managers/TrackManager.h"
#include "Rules/League_Rules.h"
#include "Subsystems/MatchManagerSubsystem.h"
#include "Subsystems/RulesSubsystem.h"


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
	OnSimulateRaceRequestDelegate.AddUObject(this, &URaceManager::SimulateRace);
}


void URaceManager::AddRacerManager(URacerMatchManager* NewRacerMatchManager, int32 RaceLineID)
{
	if (NewRacerMatchManager && !Racers.Contains(RaceLineID))
		Racers.Add(RaceLineID, NewRacerMatchManager);
}


void URaceManager::RemoveRacerManager(int32 RaceLineID)
{
	if (Racers.Contains(RaceLineID))
		Racers.Remove(RaceLineID);
}


void URaceManager::SimulateRace()
{
	if (URulesSubsystem* RulesSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<URulesSubsystem>())
	{
		CalculateRacerRatings();
		SortLinesByRating();
		TArray<FRaceLineResultData> ResultForEachLine;
		int32 Position = 0;
		URacerMatchManager* PreviousManager = nullptr;
		for (const auto& Racer : Racers)
		{
			ERaceResults Result = static_cast<ERaceResults>(Position);
			const bool IsRacerVisitor = Racer.Value->IsVisitor();
			bool HasBonus = AreRacersFromSameTeam(Position, PreviousManager, IsRacerVisitor);
		
			if (Racer.Value->GetCurrentRaceRating() == 0)
			{
				Racer.Value->AddPoints(ERaceResults::Defect, false);
				Result = ERaceResults::Defect;
			}
			else Racer.Value->AddPoints(Result, HasBonus);

			CollectRaceResults(Result, Racer.Key, *RulesSubsystem);
			CollectRaceLineData(Result, IsRacerVisitor, *RulesSubsystem, ResultForEachLine);
			PreviousManager = Racer.Value;
			Position++;
		}
		UE_LOG(LogTemp, Error, TEXT("==================================="));
		OnRaceLineResultUpdatedDelegate.Broadcast(RaceResults);
		BroadcastRaceResult(ResultForEachLine);
		OnRaceFinished();
	}
}


void URaceManager::CalculateRacerRatings()
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


bool URaceManager::AreRacersFromSameTeam(int32 Position, const TObjectPtr<URacerMatchManager>& PreviousManager, bool IsCurrentRacerVisitor)
{
	if (Position < Racers.Num() - 1 && PreviousManager)
		return PreviousManager->IsVisitor() == IsCurrentRacerVisitor;
	return false;
}


void URaceManager::CollectRaceLineData(ERaceResults Result, bool IsCurrentRacerVisitor, const URulesSubsystem& RulesSubsystem, TArray<FRaceLineResultData>& OutArray)
{
	FRaceLineResultData RaceLineResult;
	RaceLineResult.Points = RulesSubsystem.GetRaceResultNumber(Result);
	RaceLineResult.IsVisitor = IsCurrentRacerVisitor;
	OutArray.Add(RaceLineResult);
}


void URaceManager::CollectRaceResults(ERaceResults Result, int32 RaceLineID, const URulesSubsystem& RulesSubsystem)
{
	FRaceResultData Data;
	Data.RacerScore = RulesSubsystem.GetRaceResultNumber(Result);
	Data.RaceLineID = RaceLineID;
	RaceResults.Add(Data);
}


void URaceManager::BroadcastRaceResult(TArray<FRaceLineResultData>& ResultForEachLine)
{
	if (UMatchManagerSubsystem* MatchManagerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMatchManagerSubsystem>())
	{
		if (ULeague_Rules* LeagueRules = Cast<ULeague_Rules>(MatchManagerSubsystem->GetCompetitionRules()))
		{
			for (const auto& Result : ResultForEachLine)
			{
				LeagueRules->OnScoreUpdatedDelegate.Broadcast(Result.IsVisitor, Result.Points, RaceID);
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


bool URaceManager::AreAllRacersSet()
{
	if (Racers.Num() < 4) return false;
	return true;
}


FString URaceManager::GetRaceLinePoints(int32 RaceLineID)
{
	if (URulesSubsystem* RulesSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<URulesSubsystem>())
	{
		for (const auto& Racer : Racers)
		{
			if (Racer.Key == RaceLineID)
			{
				return RulesSubsystem->GetRaceResultText(Racer.Value->GetLastRaceResult());
			}
		}
	}
	return "";
}

bool URaceManager::IsNominatedRace()const{return bIsNominatedRace;}

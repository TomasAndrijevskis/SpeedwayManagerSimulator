
#include "Managers/RaceManager.h"
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


void URaceManager::AddRacerManager(URacerMatchManager* NewRacerMatchManager)
{
	if (NewRacerMatchManager && !RacerMatchManagers.Contains(NewRacerMatchManager))
		RacerMatchManagers.Add(NewRacerMatchManager);
}


void URaceManager::RemoveRacerManager(URacerMatchManager* NewRacerMatchManager)
{
	if (NewRacerMatchManager && RacerMatchManagers.Contains(NewRacerMatchManager))
		RacerMatchManagers.Remove(NewRacerMatchManager);
}


void URaceManager::SimulateRace()
{
	URulesSubsystem* RulesSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<URulesSubsystem>();
	if (!RulesSubsystem) return;
	if (UMatchManagerSubsystem* MatchManagerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMatchManagerSubsystem>())
	{
		UTrackManager* TrackManager = MatchManagerSubsystem->GetCompetitionRules()->GetTrackManager();
		if (!TrackManager) return;
		for (const auto& Racer : RacerMatchManagers)
		{
			const float StartModifier = TrackManager->GetGateModifier(Racer->CurrentRaceLineID);
			const float DrivingModifier = TrackManager->GetDrivingModifier();
			Racer->CalculateRating(StartModifier, DrivingModifier, TrackManager->GetCurrentTrackType());
		}
		SortLinesByRating();
		for (int32 Position = 0; Position < RacerMatchManagers.Num(); Position++)
		{
			ERaceResults Result = static_cast<ERaceResults>(Position);
			if (URacerMatchManager* CurrentRacer = RacerMatchManagers[Position])
			{
				const bool IsVisitor = CurrentRacer->IsVisitor();
				bool HasBonus = false;
				if (Position != 0 && Position < RacerMatchManagers.Num() - 1)
					HasBonus = RacerMatchManagers[Position - 1]->IsVisitor() == IsVisitor;
				if (CurrentRacer->GetCurrentRaceRating() == 0)
				{
					CurrentRacer->AddPoints(ERaceResults::Defect, false);
				}
				else
				{
					CurrentRacer->AddPoints(Result, HasBonus);
				}
				FRaceResultData Data;
				Data.RacerScore = RulesSubsystem->GetRaceResultNumber(Result);
				Data.RaceLineID = RacerMatchManagers[Position]->CurrentRaceLineID;
				RaceResults.Add(Data);
			}
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
		for (const auto& Racer : RacerMatchManagers)
		{
			if (ULeague_Rules* LeagueRules = Cast<ULeague_Rules>(MatchManagerSubsystem->GetCompetitionRules()))
			{
				LeagueRules->OnScoreUpdatedDelegate.Broadcast(Racer->IsVisitor(), Racer->GetScore(), RaceID);
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
	RacerMatchManagers.Sort([](const URacerMatchManager& L1, const URacerMatchManager& L2)
	{
		if (L1.GetCurrentRaceRating() == L2.GetCurrentRaceRating())
		{
			return L1.GetTieBreaker() > L2.GetTieBreaker();
		}
		return L1.GetCurrentRaceRating() > L2.GetCurrentRaceRating();
	});
}


bool URaceManager::AreAllRacersSet()
{
	if (RacerMatchManagers.Num() < 4) return false;
	return true;
}

bool URaceManager::IsNominatedRace()const{return bIsNominatedRace;}
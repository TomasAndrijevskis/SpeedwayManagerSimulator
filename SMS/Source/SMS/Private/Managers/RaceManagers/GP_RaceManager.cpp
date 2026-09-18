
#include "Managers/RaceManagers/GP_RaceManager.h"
#include "Managers/RacerMatchManager.h"
#include "Rules/GP_Rules.h"
#include "Subsystems/MatchManagerSubsystem.h"


void UGP_RaceManager::SimulateRace()
{
	if (UMatchManagerSubsystem* MatchManagerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMatchManagerSubsystem>())
	{
		CalculateRacerRatings();
		SortLinesByRating();
		int32 Position = 0;
		TArray<int32> HigherRacers;
		for (const auto& CurrentRacer : Racers)
		{
			ERaceResults Result = static_cast<ERaceResults>(Position);
			if (IsNominatedRace() && (Result == ERaceResults::First || Result == ERaceResults::Second))
			{
				if (UGP_Rules* GPRules = Cast<UGP_Rules>(MatchManagerSubsystem->GetCompetitionRules()))
				{
					FFinalQualifier Data;
					Data.Placement = Result;
					Data.RacerManager = CurrentRacer.Value;
					Data.SemifinalRaceId = RaceID;
					GPRules->AddQualifiedRacers(Data);
				}
			}
			UE_LOG(LogTemp, Warning, TEXT("================="));
			UE_LOG(LogTemp, Warning, TEXT("%s"), *CurrentRacer.Value->GetRacerName());
			HigherRacers.Add(CurrentRacer.Value->GetRacerNumber());
			for (const auto& Rival : Racers)
			{
				if (CurrentRacer.Value == Rival.Value || HigherRacers.Contains(Rival.Value->GetRacerNumber())) continue;
				UE_LOG(LogTemp, Display, TEXT("%s"), *Rival.Value->GetRacerName());
				CurrentRacer.Value->AddDefeatedRival(Rival.Value->GetRacerNumber());
			}
			ApplyRacerResult(*CurrentRacer.Value, Result, false);
			Position++;
			if (UCompetitionRules* Rules = MatchManagerSubsystem->GetCompetitionRules())
			{
				CollectRaceResults(Result, CurrentRacer.Key, *Rules);
			}
		}
		UE_LOG(LogTemp, Error, TEXT("==================================="));
		OnRaceLineResultUpdatedDelegate.Broadcast(RaceResults);
		OnRaceFinished();
	}
}

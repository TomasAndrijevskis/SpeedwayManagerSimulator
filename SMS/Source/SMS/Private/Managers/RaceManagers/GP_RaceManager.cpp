
#include "Managers/RaceManagers/GP_RaceManager.h"
#include "Managers/RacerMatchManager.h"
#include "Subsystems/RulesSubsystem.h"


void UGP_RaceManager::SimulateRace()
{
	if (URulesSubsystem* RulesSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<URulesSubsystem>())
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
			CollectRaceResults(Result, CurrentRacer.Key, *RulesSubsystem);
		}
		UE_LOG(LogTemp, Error, TEXT("==================================="));
		OnRaceLineResultUpdatedDelegate.Broadcast(RaceResults);
		OnRaceFinished();
	}
}

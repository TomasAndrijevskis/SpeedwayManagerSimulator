
#include "Managers/RaceManagers/League_RaceManager.h"
#include "Managers/RacerMatchManager.h"
#include "Rules/League_Rules.h"
#include "Subsystems/MatchManagerSubsystem.h"


void ULeague_RaceManager::SimulateRace()
{
	if (UMatchManagerSubsystem* MatchManagerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMatchManagerSubsystem>())
	{
		CalculateRacerRatings();
		SortLinesByRating();
		TArray<FRaceResultData> ResultForEachLine;
		int32 Position = 0;
		URacerMatchManager* PreviousManager = nullptr;
		for (const auto& CurrentRacer : Racers)
		{
			ERaceResults Result = static_cast<ERaceResults>(Position);
			bool HasBonus = AreRacersFromSameTeam(Position, PreviousManager, CurrentRacer.Value->IsVisitor());
			ApplyRacerResult(*CurrentRacer.Value, Result, HasBonus);
			PreviousManager = CurrentRacer.Value;
			Position++;

			if (UCompetitionRules* Rules = MatchManagerSubsystem->GetCompetitionRules())
			{
				CollectRaceResults(Result, CurrentRacer.Key, *Rules);
				CollectRaceLineData(Result, CurrentRacer.Value->GetRacerNumber(), *Rules, ResultForEachLine);
			}
		}
		UE_LOG(LogTemp, Error, TEXT("==================================="));
		OnRaceLineResultUpdatedDelegate.Broadcast(RaceResults);
		BroadcastRaceResult(ResultForEachLine);
		OnRaceFinished();
	}
}


bool ULeague_RaceManager::AreRacersFromSameTeam(int32 Position, const TObjectPtr<URacerMatchManager>& PreviousManager, bool IsCurrentRacerVisitor)
{
	if (Position < Racers.Num() - 1 && PreviousManager)
		return PreviousManager->IsVisitor() == IsCurrentRacerVisitor;
	return false;
}


void ULeague_RaceManager::CollectRaceLineData(ERaceResults Result, int32 RacerNumber, const UCompetitionRules& Rules, TArray<FRaceResultData>& OutArray)
{
	FRaceResultData RaceLineResult;
	RaceLineResult.Points = Rules.GetRaceResultAsNumber(Result);
	RaceLineResult.RacerNumber = RacerNumber;
	OutArray.Add(RaceLineResult);
}


void ULeague_RaceManager::BroadcastRaceResult(TArray<FRaceResultData>& ResultForEachLine) const
{
	if (UMatchManagerSubsystem* MatchManagerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMatchManagerSubsystem>())
	{
		if (ULeague_Rules* LeagueRules = Cast<ULeague_Rules>(MatchManagerSubsystem->GetCompetitionRules()))
		{
			for (const auto& Result : ResultForEachLine)
			{
				LeagueRules->OnScoreUpdatedDelegate.Broadcast(Result.IsVisitor(), Result.Points, RaceID);
			}
		}
	}
}


void ULeague_RaceManager::RemoveRacerManager(int32 RaceLineID)
{
	if (Racers.Contains(RaceLineID)) Racers.Remove(RaceLineID);
}
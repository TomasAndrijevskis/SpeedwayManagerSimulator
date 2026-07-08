#pragma once

#include "CoreMinimal.h"
#include "Data/RacersData/RacerMatchData.h"
#include "TeamMatchData.generated.h"


USTRUCT(BlueprintType)
struct FTeamMatchData
{
	GENERATED_BODY()
	
	UPROPERTY()
	int TeamID;

	UPROPERTY()
	FText TeamName;
	
	UPROPERTY()
	TArray<FRacerData> Racers;

	UPROPERTY()
	bool IsVisitorTeam;

	UPROPERTY()
	int TeamScore = 0;

	UPROPERTY()
	int LastRaceScore = 0;
};

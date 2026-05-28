#pragma once

#include "CoreMinimal.h"
#include "ETeams.h"
#include "Data/RacersData/RacerData.h"
#include "TeamRosterData.generated.h"


USTRUCT(BlueprintType)
struct FTeamRosterData
{
	GENERATED_BODY()
	
	UPROPERTY()
	int TeamID;

	UPROPERTY()
	FText TeamName;
	
	UPROPERTY()
	TMap<FString, FRacerData> Racers;
};

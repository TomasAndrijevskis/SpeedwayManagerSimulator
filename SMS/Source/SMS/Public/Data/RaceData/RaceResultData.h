#pragma once

#include "CoreMinimal.h"
#include "RaceResultData.generated.h"


USTRUCT(BlueprintType)
struct FRaceResultData
{
	GENERATED_BODY()
	
	UPROPERTY()
	int32 RaceLineID = 0;

	UPROPERTY()
	int32 RacerScore = 0;
};

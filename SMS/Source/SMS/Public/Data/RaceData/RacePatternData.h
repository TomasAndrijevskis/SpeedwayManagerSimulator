#pragma once

#include "CoreMinimal.h"
#include "RaceLineData.h"
#include "RacePatternData.generated.h"


USTRUCT(BlueprintType)
struct FRacePatternData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	TArray<FRaceLineData> RaceLines;

	UPROPERTY(EditDefaultsOnly)
	bool IsNominatedRace = false;
};

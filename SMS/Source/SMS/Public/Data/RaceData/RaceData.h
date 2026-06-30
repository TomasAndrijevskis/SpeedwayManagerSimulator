#pragma once

#include "CoreMinimal.h"
#include "RaceLineData.h"
#include "RaceData.generated.h"


USTRUCT(BlueprintType)
struct FRaceData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	TArray<FRaceLineData> RaceLines;

	UPROPERTY(EditDefaultsOnly)
	bool IsNominatedRace = false;
};

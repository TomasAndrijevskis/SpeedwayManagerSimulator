#pragma once

#include "CoreMinimal.h"
#include "RacerStats.generated.h"


USTRUCT(BlueprintType)
struct FRacerStats
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int Rating;
};

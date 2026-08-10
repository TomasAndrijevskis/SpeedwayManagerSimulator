#pragma once

#include "CoreMinimal.h"
#include "RacerAttributes.generated.h"


USTRUCT(BlueprintType)
struct FRacerStats
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int32 Rating = 0;
};

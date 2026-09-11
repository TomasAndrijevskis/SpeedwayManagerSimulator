#pragma once

#include "CoreMinimal.h"
#include "RaceLineResultData.generated.h"


USTRUCT(BlueprintType)
struct FRaceLineResultData
{
	GENERATED_BODY()

	UPROPERTY()
	int32 Points;

	UPROPERTY()
	bool IsVisitor = false;
};

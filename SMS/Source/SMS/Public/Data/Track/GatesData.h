#pragma once

#include "CoreMinimal.h"
#include "ETrackTypes.h"
#include "GatesData.generated.h"

USTRUCT(BlueprintType)
struct FGatesData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "-1", ClampMax = "1"))
	TMap<ETrackTypes, float> StartModifiers;
};

#pragma once

#include "CoreMinimal.h"
#include "ETrackTypes.h"
#include "GatesData.generated.h"

USTRUCT(BlueprintType)
struct FGatesData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TMap<ETrackTypes, float> StartModifiers;
};

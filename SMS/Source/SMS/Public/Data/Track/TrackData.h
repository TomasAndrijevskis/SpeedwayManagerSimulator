#pragma once

#include "CoreMinimal.h"
#include "ETrackTypes.h"
#include "GatesData.h"
#include "TrackData.generated.h"

USTRUCT(BlueprintType)
struct FTrackData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0", ClampMax = "1"))
	TMap<ETrackTypes, float> TrackTypeProbability;

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0", ClampMax = "1"))
	float ChanceToChange = 0.f;
	
	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "-1", ClampMax = "1"))
	TMap<ETrackTypes, float> DrivingModifiers;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<FGatesData> Gates;
};

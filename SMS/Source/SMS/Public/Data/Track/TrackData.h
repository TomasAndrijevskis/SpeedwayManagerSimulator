#pragma once

#include "CoreMinimal.h"
#include "ETrackTypes.h"
#include "GatesData.h"
#include "TrackData.generated.h"

USTRUCT(BlueprintType)
struct FTrackData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	TMap<ETrackTypes, float> TrackTypeProbability;

	UPROPERTY(EditDefaultsOnly)
	float ChanceToChange = 0.f;
	
	UPROPERTY(EditDefaultsOnly)
	TMap<ETrackTypes, float> DrivingModifiers;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<FGatesData> Gates;
};

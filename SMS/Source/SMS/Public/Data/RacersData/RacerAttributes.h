#pragma once

#include "CoreMinimal.h"
#include "Data/Track/ETrackTypes.h"
#include "RacerAttributes.generated.h"


USTRUCT(BlueprintType)
struct FRacerStats
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0", ClampMax = "15"))
	int32 Rating = 0;
	
	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0", ClampMax = "10"))
	int32 Reaction = 0;

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "-5", ClampMax = "5"))
	int32 Adaptability = 0;
	
	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0", ClampMax = "10"))
	TMap<ETrackTypes, int32> DrivingSkillsOnEachTrack;
};


#pragma once

#include "CoreMinimal.h"
#include "RaceData.generated.h"


USTRUCT(BlueprintType)
struct FRaceData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	TArray<FColor> HelmetColors;

	UPROPERTY(EditDefaultsOnly)
	TArray<int> RacerIDs;
};

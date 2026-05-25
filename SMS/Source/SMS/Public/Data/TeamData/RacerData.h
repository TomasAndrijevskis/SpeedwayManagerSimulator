#pragma once

#include "CoreMinimal.h"
#include "RacerData.generated.h"


USTRUCT(BlueprintType)
struct FRacerData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly)
	int Rating;
};

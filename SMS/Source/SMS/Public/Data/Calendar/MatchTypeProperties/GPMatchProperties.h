#pragma once

#include "CoreMinimal.h"
#include "Data/Locations/ECountries.h"
#include "GPMatchProperties.generated.h"


USTRUCT(BlueprintType)
struct FGPMatchProperties
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	int32 Round = 0;
	
	UPROPERTY(EditDefaultsOnly)
	ECountries Location;
};

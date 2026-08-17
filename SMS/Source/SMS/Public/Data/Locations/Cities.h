#pragma once

#include "CoreMinimal.h"
#include "CityData.h"
#include "ECities.h"
#include "Cities.generated.h"


USTRUCT(BlueprintType)
struct FCities
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TMap<ECities, FCityData> City;
	
};


#pragma once

#include "CoreMinimal.h"
#include "Cities.h"
#include "ECountries.h"
#include "Engine/DataAsset.h"
#include "LocationsDataAsset.generated.h"


UCLASS()
class SMS_API ULocationsDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly)
	TMap<ECountries, FCities> Locations;


};

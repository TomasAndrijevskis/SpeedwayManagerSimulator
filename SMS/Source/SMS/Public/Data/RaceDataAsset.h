
#pragma once

#include "CoreMinimal.h"
#include "RaceData.h"
#include "Engine/DataAsset.h"
#include "RaceDataAsset.generated.h"

UCLASS()
class SMS_API URaceDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly)
	TMap<int, FRaceData> RacePatterns;

};

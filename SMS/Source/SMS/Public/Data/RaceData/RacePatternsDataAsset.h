
#pragma once

#include "CoreMinimal.h"
#include "RaceData.h"
#include "Engine/DataAsset.h"
#include "RacePatternsDataAsset.generated.h"

UCLASS()
class SMS_API URacePatternsDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly)
	TMap<int, FRaceData> RacePatterns;
};

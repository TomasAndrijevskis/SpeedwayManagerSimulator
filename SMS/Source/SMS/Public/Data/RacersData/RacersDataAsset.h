
#pragma once

#include "CoreMinimal.h"
#include "RacerData.h"
#include "Engine/DataAsset.h"
#include "RacersDataAsset.generated.h"

UCLASS()
class SMS_API URacersDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly)
	TArray<FRacerData> Racers;
};

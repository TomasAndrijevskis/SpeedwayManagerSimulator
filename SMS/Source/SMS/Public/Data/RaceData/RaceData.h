#pragma once

#include "CoreMinimal.h"
#include "RaceData.generated.h"


class URaceLineupManager;
class URaceManager;

USTRUCT(BlueprintType)
struct FRaceData
{
	GENERATED_BODY()
	
	UPROPERTY()
	URaceManager* RaceManager;
	
	UPROPERTY()
	URaceLineupManager* RaceLineupManager;
};

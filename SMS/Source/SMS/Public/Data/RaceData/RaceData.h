#pragma once

#include "CoreMinimal.h"
#include "RaceData.generated.h"


class URaceLineupManager;
class URaceManager_Base;

USTRUCT(BlueprintType)
struct FRaceData
{
	GENERATED_BODY()
	
	UPROPERTY()
	URaceManager_Base* RaceManager = nullptr;
	
	UPROPERTY()
	URaceLineupManager* RaceLineupManager = nullptr;
};

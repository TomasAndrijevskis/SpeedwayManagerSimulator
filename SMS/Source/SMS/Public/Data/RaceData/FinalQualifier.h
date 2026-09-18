#pragma once

#include "CoreMinimal.h"
#include "Data/Rules/ERaceResults.h"
#include "FinalQualifier.generated.h"


class URacerMatchManager;

USTRUCT(BlueprintType)
struct FFinalQualifier
{
	GENERATED_BODY()
	
	UPROPERTY()
	URacerMatchManager* RacerManager = nullptr;

	UPROPERTY()
	int32 SemifinalRaceId = 0;

	ERaceResults Placement;
};

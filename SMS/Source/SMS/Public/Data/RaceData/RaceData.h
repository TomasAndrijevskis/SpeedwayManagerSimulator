#pragma once

#include "CoreMinimal.h"
#include "EHelmetColour.h"
#include "RaceData.generated.h"


USTRUCT(BlueprintType)
struct FRaceData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	TArray<EHelmetColour> HelmetColours;

	UPROPERTY(EditDefaultsOnly)
	bool IsNominatedRace = false;
	
	UPROPERTY(EditDefaultsOnly, meta = (EditCondition = "!IsNominatedRace"))
	TArray<int> RacerIDs;
};

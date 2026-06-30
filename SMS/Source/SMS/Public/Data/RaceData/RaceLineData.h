#pragma once

#include "CoreMinimal.h"
#include "EHelmetColour.h"
#include "RaceLineData.generated.h"


USTRUCT(BlueprintType)
struct FRaceLineData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	EHelmetColour HelmetColour;
	
	UPROPERTY(EditDefaultsOnly)
	int RacerIDs;
	
	bool IsVisitor() const
	{
		return HelmetColour == EHelmetColour::White || HelmetColour == EHelmetColour::Yellow;
	};
};

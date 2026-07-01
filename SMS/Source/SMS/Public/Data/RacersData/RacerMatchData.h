#pragma once

#include "CoreMinimal.h"
#include "RacerData.h"
#include "RacerMatchData.generated.h"


class URacerManager;

USTRUCT(BlueprintType)
struct FRacerMatchData
{
	GENERATED_BODY()

	UPROPERTY()
	FRacerData RacerData;

	UPROPERTY()
	int RacerNumber;

	bool IsVisitor() const
	{
		return RacerNumber >= 7;
	};
};

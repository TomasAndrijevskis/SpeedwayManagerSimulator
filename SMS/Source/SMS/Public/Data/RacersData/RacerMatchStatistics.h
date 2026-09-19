#pragma once

#include "CoreMinimal.h"
#include "Data/Rules/ERaceResults.h"
#include "RacerMatchStatistics.generated.h"


USTRUCT()
struct FMatchStatistics
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<ERaceResults> RaceResults;

	UPROPERTY()
	bool bIsVisitor;

	UPROPERTY()
	int32 Bonuses;
};
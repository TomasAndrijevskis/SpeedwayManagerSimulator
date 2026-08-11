#pragma once

#include "CoreMinimal.h"
#include "Data/Rules/ERaceResults.h"
#include "MatchStatistics.generated.h"


USTRUCT()
struct FMatchStatistics
{
	GENERATED_BODY()
	
	TArray<ERaceResults> RaceResults;

	bool bIsVisitor;

	int32 Bonuses;
};
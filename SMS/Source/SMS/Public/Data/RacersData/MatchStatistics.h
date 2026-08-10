#pragma once

#include "CoreMinimal.h"
#include "MatchStatistics.generated.h"


USTRUCT()
struct FMatchStatistics
{
	GENERATED_BODY()
	
	TArray<FString> RacerPoints;

	bool bIsVisitor;

	int32 Bonuses;
};
#pragma once

#include "CoreMinimal.h"
#include "RacerMatchStatistics.h"
#include "RacerStatistics.generated.h"


USTRUCT()
struct FRacerStatistics
{
	GENERATED_BODY()

	UPROPERTY()
	int32 RacerID = 0;

	UPROPERTY()
	FString RacerName = "";

	UPROPERTY()
	int32 RacerAge = 0;

	UPROPERTY()
	FString TeamName = "";
	
	TArray<FMatchStatistics> MatchStatistics;
};
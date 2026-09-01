#pragma once

#include "CoreMinimal.h"
#include "TeamsInMatch.h"
#include "CalendarPatternData.generated.h"


USTRUCT(BlueprintType)
struct FCalendarPatternData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int32 Week = 0;

	UPROPERTY(EditDefaultsOnly)
	TArray<FTeamsInMatch> Races;

	UPROPERTY(EditDefaultsOnly)
	bool IsPlayoffs;
};

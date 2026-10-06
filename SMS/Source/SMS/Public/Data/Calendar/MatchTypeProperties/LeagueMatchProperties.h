#pragma once

#include "CoreMinimal.h"
#include "Data/Calendar/TeamsInMatch.h"
#include "LeagueMatchProperties.generated.h"


USTRUCT(BlueprintType)
struct FLeagueMatchProperties
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	int32 Round = 0;

	UPROPERTY(EditDefaultsOnly)
	TArray<FTeamsInMatch> TeamPairs;

	UPROPERTY(EditDefaultsOnly)
	bool IsPlayoffs;
};

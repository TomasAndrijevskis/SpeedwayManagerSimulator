#pragma once

#include "CoreMinimal.h"
#include "TeamMatchStatistics.h"
#include "TeamStatistics.generated.h"


USTRUCT()
struct FTeamStatistics
{
	GENERATED_BODY()
	
	UPROPERTY()
	int32 TeamID = 0;

	UPROPERTY()
	FString TeamName = "";

	TArray<FTeamMatchStatistics> MatchStatistics;
};

#pragma once

#include "CoreMinimal.h"
#include "Data/Rules/EMatchResults.h"
#include "TeamMatchStatistics.generated.h"


USTRUCT()
struct FTeamMatchStatistics
{
	GENERATED_BODY()

	UPROPERTY()
	bool IsVisitorTeam;

	UPROPERTY()
	int32 TeamScore = 0;
	
	UPROPERTY()
	EMatchResults Result;
	
	TMap<int32, int32> OpponentResult;
};

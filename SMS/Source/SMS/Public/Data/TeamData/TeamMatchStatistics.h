#pragma once

#include "CoreMinimal.h"
#include "Data/Rules/EMatchResults.h"
#include "Data/TeamData/ETeams.h"
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
	
	//uproperty
	TMap<ETeams, int32> OpponentResult;
};

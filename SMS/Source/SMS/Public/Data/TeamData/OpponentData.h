#pragma once

#include "CoreMinimal.h"
#include "OpponentData.generated.h"


USTRUCT()
struct FOpponentData
{
	GENERATED_BODY()
	
	UPROPERTY()
	int32 OpponentTeamScore = 0;

	UPROPERTY()
	int32 TeamOpponentID = 0;
};

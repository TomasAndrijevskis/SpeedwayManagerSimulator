#pragma once

#include "CoreMinimal.h"
#include "TeamsInMatch.generated.h"


USTRUCT(BlueprintType)
struct FTeamsInMatch
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int32 HomeTeamID = 0;
	
	UPROPERTY(EditDefaultsOnly)
	int32 VisitorTeamID = 0;
	
};

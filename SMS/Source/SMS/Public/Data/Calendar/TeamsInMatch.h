#pragma once

#include "CoreMinimal.h"
#include "TeamsInMatch.generated.h"


USTRUCT(BlueprintType)
struct FTeamsInMatch
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int32 HomeTeam = 0;

	UPROPERTY(EditDefaultsOnly)
	int32 VisitorTeam = 0;
};

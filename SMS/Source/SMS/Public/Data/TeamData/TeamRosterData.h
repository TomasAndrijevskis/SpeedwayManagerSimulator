#pragma once

#include "CoreMinimal.h"
#include "ETeams.h"
#include "TeamRosterData.generated.h"


USTRUCT(BlueprintType)
struct FTeamRosterData
{
	GENERATED_BODY()
	
	UPROPERTY()
	TEnumAsByte<ETeams> TeamID;

	UPROPERTY()
	TArray<FString> Racers;
};

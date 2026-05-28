#pragma once

#include "CoreMinimal.h"
#include "ETeams.h"
#include "TeamRosterData.generated.h"


USTRUCT(BlueprintType)
struct FTeamRosterData
{
	GENERATED_BODY()
	
	UPROPERTY()
	int TeamID;

	UPROPERTY()
	FText TeamName;
	
	UPROPERTY()
	TArray<FString> Racers;
};

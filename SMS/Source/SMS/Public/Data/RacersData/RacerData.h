#pragma once

#include "CoreMinimal.h"
#include "RacerStats.h"
#include "Data/TeamData/ETeams.h"
#include "RacerData.generated.h"


USTRUCT(BlueprintType)
struct FRacerData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly)
	int ID;

	UPROPERTY(EditDefaultsOnly)
	int Age;

	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<ETeams> InitialTeam;
	
	UPROPERTY(EditDefaultsOnly)
	FRacerStats RacerStats;
};

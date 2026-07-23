#pragma once

#include "CoreMinimal.h"
#include "RacerStats.h"
#include "Data/TeamData/ETeams.h"
#include "RacerData.generated.h"


USTRUCT(BlueprintType)
struct FRacerData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int32 ID = 0;
	
	UPROPERTY(EditDefaultsOnly)
	FString Name = "";

	UPROPERTY(EditDefaultsOnly)
	int32 Age = 0;

	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<ETeams> InitialTeam;
	
	UPROPERTY(EditDefaultsOnly)
	FRacerStats RacerStats;
};

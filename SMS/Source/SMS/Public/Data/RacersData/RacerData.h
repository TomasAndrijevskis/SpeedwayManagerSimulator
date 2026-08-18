#pragma once

#include "CoreMinimal.h"
#include "RacerAttributes.h"
#include "Data/Locations/ECountries.h"
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
	ECountries Nationality = ECountries::None;
	
	UPROPERTY(EditDefaultsOnly)
	ETeams InitialTeam;
	
	UPROPERTY(EditDefaultsOnly)
	FRacerStats RacerStats;
};

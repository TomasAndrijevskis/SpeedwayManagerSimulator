
#pragma once

#include "CoreMinimal.h"
#include "RacerData.h"
#include "Engine/DataAsset.h"
#include "TeamLineupsDataAsset.generated.h"

UCLASS()
class SMS_API UTeamLineupsDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	TArray<FRacerData> Team_Lokomotive;

	UPROPERTY(EditDefaultsOnly)
	TArray<FRacerData> Team_Sparta;
};

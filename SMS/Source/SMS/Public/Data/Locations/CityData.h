#pragma once

#include "CoreMinimal.h"
#include "Data/TeamData/ETeams.h"
#include "CityData.generated.h"

class UTrackDataAsset;

USTRUCT(BlueprintType)
struct FCityData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	bool HasTeam = false;

	UPROPERTY(EditDefaultsOnly, meta = (EditCondition = "HasTeam", EditConditionHides))
	ETeams Team;

	UPROPERTY(EditDefaultsOnly)
	UTrackDataAsset* TrackDataAsset = nullptr;
};

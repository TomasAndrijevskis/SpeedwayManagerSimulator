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

	UPROPERTY(EditDefaultsOnly, meta = (EditCondition = "HasTeam"))
	ETeams Team;

	UPROPERTY(EditDefaultsOnly)
	UTrackDataAsset* TrackData = nullptr;
};

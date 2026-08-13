
#pragma once

#include "CoreMinimal.h"
#include "TrackData.h"
#include "Data/TeamData/ETeams.h"
#include "Engine/DataAsset.h"
#include "TrackDataAsset.generated.h"


UCLASS()
class SMS_API UTrackDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly)
	TMap<TEnumAsByte<ETeams>, FTrackData> TrackData;
};

#pragma once

#include "CoreMinimal.h"
#include "Data/RacersData/RacerMatchData.h"
#include "Data/Track/TrackData.h"
#include "TeamData.generated.h"


class URacerCareerManager;

USTRUCT(BlueprintType)
struct FTeamData
{
	GENERATED_BODY()
	
	UPROPERTY()
	ETeams Team = ETeams::Nothing;
	
	UPROPERTY()
	TArray<TObjectPtr<URacerCareerManager>> Racers;
	
	UPROPERTY()
	FTrackData TrackData;

	FString GetTeamName() const
	{
		return UEnum::GetDisplayValueAsText(Team).ToString();
	}
};

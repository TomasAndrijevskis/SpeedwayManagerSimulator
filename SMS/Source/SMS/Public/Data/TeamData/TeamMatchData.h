#pragma once

#include "CoreMinimal.h"
#include "Data/RacersData/RacerMatchData.h"
#include "Data/Track/TrackData.h"
#include "TeamMatchData.generated.h"


USTRUCT(BlueprintType)
struct FTeamMatchData
{
	GENERATED_BODY()
	
	UPROPERTY()
	int32 TeamID = 0;

	UPROPERTY()
	FString TeamName = "";
	
	UPROPERTY()
	TArray<FRacerData> Racers;
	
	UPROPERTY()
	bool IsVisitorTeam;

	UPROPERTY()
	FTrackData TrackData;
	
	UPROPERTY()
	int32 TeamScore = 0;

	UPROPERTY()
	int32 LastRaceScore = 0;
};

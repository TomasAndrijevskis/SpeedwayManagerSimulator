
#pragma once

#include "CoreMinimal.h"
#include "Data/RaceData/RaceResultData.h"
#include "RaceStatsManager.generated.h"


class URaceLineStat;

UCLASS()
class SMS_API URaceStatsManager : public UObject
{
	GENERATED_BODY()

public:

	void AddRaceLineStat(URaceLineStat* NewRaceLineStat);

	void HandleStatUpdate(const TArray<FRaceResultData>& RaceResultData);
	
private:

	UPROPERTY()
	TArray<TObjectPtr<URaceLineStat>> RaceLineStats;

	int32 OverallPoints = 0;
};

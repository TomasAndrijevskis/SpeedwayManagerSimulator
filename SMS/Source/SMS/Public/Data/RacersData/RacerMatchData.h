#pragma once

#include "CoreMinimal.h"
#include "RacerData.h"
#include "RacerMatchData.generated.h"


USTRUCT(BlueprintType)
struct FRacerMatchData
{
	GENERATED_BODY()

	UPROPERTY()
	FRacerData RacerData;

	//number during match 1-6 / 7-12
	UPROPERTY()
	int RacerNumber;

	bool IsVisitor() const
	{
		return RacerNumber >= 7;
	}

	bool IsJunior() const
	{
		return RacerData.Age <= 23 && (RacerNumber == 5 || RacerNumber == 11);
	}

	bool IsU26Racer() const
	{
		return RacerData.Age <= 26;
	}

	bool IsReplacement() const
	{
		return RacerNumber == 6 || RacerNumber == 12;
	}

	int GetBaseRating() const
	{
		return RacerData.RacerStats.Rating;
	}

	FString GetRacerName() const
	{
		return RacerData.Name;
	}
};

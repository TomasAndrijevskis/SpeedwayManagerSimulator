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

	bool IsOnJuniorPosition() const
	{
		return RacerNumber == 5 || RacerNumber == 11;
	}

	int GetBaseRating() const
	{
		return RacerData.RacerStats.Rating;
	}

	int GetRacerNumber() const
	{
		return RacerNumber;
	}
	
	int GetRacerAge() const
	{
		return RacerData.Age;
	}
	
	FString GetRacerName() const
	{
		return RacerData.Name;
	}
};

#pragma once

#include "CoreMinimal.h"
#include "MatchID.generated.h"


USTRUCT(BlueprintType)
struct FMatchID
{
	GENERATED_BODY()

	UPROPERTY()
	int32 Season = 0;

	UPROPERTY()
	int32 Week = 0;

	UPROPERTY()
	int32 WeekMatchNumber = 0;

	bool operator==(const FMatchID& Other) const
    {
        return Season == Other.Season && Week == Other.Week && WeekMatchNumber == Other.WeekMatchNumber;
    }
	
	friend uint32 GetTypeHash(const FMatchID& ID)
	{
		return HashCombine(HashCombine(GetTypeHash(ID.Season), GetTypeHash(ID.Week)), GetTypeHash(ID.WeekMatchNumber));
	}
};

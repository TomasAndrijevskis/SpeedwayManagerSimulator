#pragma once

#include "CoreMinimal.h"
#include "ECompetitionType.h"
#include "MatchID.h"
#include "MatchData.generated.h"


USTRUCT(BlueprintType)
struct FMatchData
{
	GENERATED_BODY()

	UPROPERTY()
	FMatchID MatchID;
	
	UPROPERTY()
	ECompetitionType CompetitionType = ECompetitionType::None;

	UPROPERTY()
	bool bCompleted = false;

	bool operator==(const FMatchData& Other) const
	{
		return MatchID == Other.MatchID && CompetitionType == Other.CompetitionType && bCompleted == Other.bCompleted;
	}
	
	friend uint32 GetTypeHash(const FMatchData& Data)
	{
		return HashCombine(HashCombine(GetTypeHash(Data.MatchID), GetTypeHash(Data.CompetitionType)), GetTypeHash(Data.bCompleted));
	}
};

#pragma once

#include "CoreMinimal.h"
#include "TeamMatchStatistics.h"
#include "TeamStatistics.generated.h"


USTRUCT()
struct FTeamStatistics
{
	GENERATED_BODY()
	
	UPROPERTY()
	ETeams Team = ETeams::Nothing;

	TArray<FTeamMatchStatistics> MatchStatistics;

	FString GetTeamName() const
	{
		return UEnum::GetDisplayValueAsText(Team).ToString();
	}
};

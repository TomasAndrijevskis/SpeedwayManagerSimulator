#pragma once

#include "CoreMinimal.h"
#include "ECompetitionType.h"
#include "MatchTypeProperties/GPMatchProperties.h"
#include "MatchTypeProperties/LeagueMatchProperties.h"
#include "CalendarPatternData.generated.h"


USTRUCT(BlueprintType)
struct FCalendarPatternData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	ECompetitionType CompetitionType = ECompetitionType::None;
	
	UPROPERTY(EditDefaultsOnly, meta=(EditCondition = "CompetitionType == ECompetitionType::League", EditConditionHides))
	FLeagueMatchProperties LeagueMatches;
	
	UPROPERTY(EditDefaultsOnly, meta=(EditCondition = "CompetitionType == ECompetitionType::GP", EditConditionHides))
	FGPMatchProperties GPMatch;
};

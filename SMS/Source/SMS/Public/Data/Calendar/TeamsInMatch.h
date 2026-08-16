#pragma once

#include "CoreMinimal.h"
#include "Data/TeamData/ETeams.h"
#include "TeamsInMatch.generated.h"


USTRUCT(BlueprintType)
struct FTeamsInMatch
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	ETeams HomeTeam = ETeams::Nothing;

	UPROPERTY(EditDefaultsOnly)
	ETeams VisitorTeam =  ETeams::Nothing;
};

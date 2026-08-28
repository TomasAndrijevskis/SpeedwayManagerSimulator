#pragma once

#include "CoreMinimal.h"
#include "TeamsInMatch.generated.h"


USTRUCT(BlueprintType)
struct FTeamsInMatch
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	//ETeams HomeTeam = ETeams::Nothing;
	int32 HomeTeamID = 0;
	
	UPROPERTY(EditDefaultsOnly)
	//ETeams VisitorTeam =  ETeams::Nothing;
	int32 VisitorTeamID = 0;
	
};

#pragma once

#include "CoreMinimal.h"
#include "ETeams.h"
#include "TeamData.generated.h"


USTRUCT(BlueprintType)
struct FTeamData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<ETeams> TeamID;
	
};

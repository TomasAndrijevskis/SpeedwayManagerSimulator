
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RaceFunctionLibrary.generated.h"


UCLASS()
class SMS_API URaceFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	static bool IsReplacementPossible(int OwnTeamPts, int EnemyTeamPts);

};

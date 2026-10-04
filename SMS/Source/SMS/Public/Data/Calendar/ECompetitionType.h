
#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class ECompetitionType : uint8
{
	None UMETA(DisplayName = "None"),
	League UMETA(DisplayName = "League"),
	GP UMETA(DisplayName = "Grand Prix"),
	JGP UMETA(DisplayName = "Junior Grand Prix"),
	GPCH UMETA(DisplayName = "Grand Prix Challenge"),
	SWC UMETA(DisplayName = "World Cup"),
	SON UMETA(DisplayName = "Speedway Of Nations"),
};


#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class ETrackTypes : uint8
{
	None UMETA(DisplayName = "None"),
	Hard UMETA(DisplayName = "Hard"),
	Normal UMETA(DisplayName = "Normal"),
	Grip UMETA(DisplayName = "Grip"),
};

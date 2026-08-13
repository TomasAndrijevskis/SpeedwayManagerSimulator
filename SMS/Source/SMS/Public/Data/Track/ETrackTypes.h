
#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class ETrackTypes : uint8
{
	Hard UMETA(DisplayName = "Hard"),
	Normal UMETA(DisplayName = "Normal"),
	Grip UMETA(DisplayName = "Grip"),
};

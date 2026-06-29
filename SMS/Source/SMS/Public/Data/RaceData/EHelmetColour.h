
#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class EHelmetColour : uint8
{
	Empty UMETA(DisplayName = "None Selected"),
	White UMETA(DisplayName = "White"),
	Yellow UMETA(DisplayName = "Yellow"),
	Red UMETA(DisplayName = "Red"),
	Blue UMETA(DisplayName = "Blue"),
};

namespace HelmetColours
{
	FLinearColor GetHelmetColour(EHelmetColour Colour);
}
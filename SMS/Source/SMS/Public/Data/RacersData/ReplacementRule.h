#pragma once

#include "CoreMinimal.h"
#include "ReplacementRule.generated.h"

USTRUCT(BlueprintType)
struct FReplacementRule
{
	GENERATED_BODY()

	FReplacementRule() = default;
	
	FReplacementRule(int32 NewMaxReplacements, EPositionTypes NewPositionType)
	: MaxReplacements(NewMaxReplacements), PositionType(NewPositionType){}
	
	int32 MaxReplacements = 0;
	
	EPositionTypes PositionType;
	
};

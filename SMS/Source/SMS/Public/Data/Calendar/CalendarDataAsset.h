
#pragma once

#include "CoreMinimal.h"
#include "CalendarPatternData.h"
#include "Engine/DataAsset.h"
#include "CalendarDataAsset.generated.h"

UCLASS()
class SMS_API UCalendarDataAsset : public UDataAsset
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TArray<FCalendarPatternData> Rounds;
};

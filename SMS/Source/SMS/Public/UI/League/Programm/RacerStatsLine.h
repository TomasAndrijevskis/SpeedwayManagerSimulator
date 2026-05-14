
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RacerStatsLine.generated.h"

class UNamesBox;
class UNumbersBox;
class UTextBlock;
class UHorizontalBox;

UCLASS()
class SMS_API URacerStatsLine : public UUserWidget
{
	GENERATED_BODY()

private:

	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_RiderNumber;
	
	UPROPERTY(meta = (BindWidget))
	UNamesBox* NamesBox_RacerName;

	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_OverallPoints;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HB_Points;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UNumbersBox> PointsBoxClass;
};

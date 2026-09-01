
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GP_RacerStatsLine.generated.h"

class UHorizontalBox;
class UNumbersBox;
class UNamesBox;

UCLASS()
class SMS_API UGP_RacerStatsLine : public UUserWidget
{
	GENERATED_BODY()

public:

private:

	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_RacerNumber;
	
	UPROPERTY(meta = (BindWidget))
	UNamesBox* NamesBox_RacerName;
	
	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_OverallPoints;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HB_Points;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UNumbersBox> PointsBoxClass;
};

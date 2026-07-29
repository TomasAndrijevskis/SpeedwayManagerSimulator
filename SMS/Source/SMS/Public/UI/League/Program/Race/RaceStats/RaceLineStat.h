
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RaceLineStat.generated.h"


class UVerticalBox;
class UTextBlock;
class UNumbersBox;
class UProgressBar;

UCLASS()
class SMS_API URaceLineStat : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetID(int32 RaceLineID);
	int32 GetID() const;
	
	void UpdateNumbers(int32 PointsToAdd);

	void UpdateProgressBar(int32 OverallPoints);
	
private:

	UPROPERTY(meta = (BindWidget))
	UProgressBar* ProgressBar;

	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_RaceLine;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock_PointsAmount;

	int32 CurrentPoints = 0;
	
	int32 ID;
};

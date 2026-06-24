
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NominatedRaceLine.generated.h"


class UChooseBox;
class UNumbersBox;

UCLASS()
class SMS_API UNominatedRaceLine : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void SetData(const FColor& NewHelmetColour, int NewRacerID);
	
private:

	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_RacerNumber;

	UPROPERTY(meta = (BindWidget))
	UChooseBox* ChooseBox_ChooseRacer;

	int RacerID;
};

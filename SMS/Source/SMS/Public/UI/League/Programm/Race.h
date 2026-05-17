
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Race.generated.h"

class UNumbersBox;
class UScoreCounter;
class UTextBlock;
class URaceLine;

UCLASS()
class SMS_API URace : public UUserWidget
{
	GENERATED_BODY()

public:

	void SimulateRace();

	void FindAndSetRacer(FString RacerName, int ID);
	
protected:

	virtual void NativeConstruct() override;
	
private:

	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_RaceNumber;
	
	UPROPERTY(meta = (BindWidget))
	URaceLine* RaceLine_First;

	UPROPERTY(meta = (BindWidget))
	URaceLine* RaceLine_Second;
	
	UPROPERTY(meta = (BindWidget))
	URaceLine* RaceLine_Third;
	
	UPROPERTY(meta = (BindWidget))
	URaceLine* RaceLine_Fourth;

	UPROPERTY(meta = (BindWidget))
	UScoreCounter* ScoreCounter;

	void SortArray();
	
	TArray<URaceLine*> RaceLines;
};

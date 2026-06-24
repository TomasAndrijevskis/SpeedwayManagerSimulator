
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NominatedRace.generated.h"


class UNominatedRaceLine;
class UVerticalBox;
class UNumbersBox;

UCLASS()
class SMS_API UNominatedRace : public UUserWidget
{
	GENERATED_BODY()

public:

	void InitializeWidget(int NewRaceID);
	
private:

	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_RaceNumber;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VB_Content;

	void CreateNominatedRaceLines();

	UNominatedRaceLine* CreateNominatedRaceLine();

	void SetRaceID(int NewID);
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UNominatedRaceLine> NominatedRaceLineClass;

	UPROPERTY()
	TArray<UNominatedRaceLine*> NominatedRaceLines;

	int RaceID;
};

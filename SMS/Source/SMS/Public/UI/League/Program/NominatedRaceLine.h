
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/RaceData/RaceLineData.h"
#include "NominatedRaceLine.generated.h"


class UTeamManager;
class UChooseBox;
class UNumbersBox;

UCLASS()
class SMS_API UNominatedRaceLine : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void SetRaceLineID(int NewID);
	
	void SetRacerID(int NewRacerID);

	void SetRaceLineData(const FRaceLineData& NewRaceLineData, const TArray<UTeamManager*>& TeamManagers);

	void FillOptions();

	void AddOption(const FString& RacerName);
	
private:

	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_RacerNumber;

	UPROPERTY(meta = (BindWidget))
	UChooseBox* ChooseBox_ChooseRacer;

	int RacerID;

	int RaceLineID;
	
	FRaceLineData RaceLineData;

	UPROPERTY()
	UTeamManager* TeamManager;
};
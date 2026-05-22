
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Race.generated.h"

class UVerticalBox;
class UPointsManager;
class URaceDataAsset;
class UNumbersBox;
class UScoreCounter;
class UTextBlock;
class URaceLine;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnOverallScoreUpdated, int, int);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRaceFinished, int, int);
UCLASS()
class SMS_API URace : public UUserWidget
{
	GENERATED_BODY()

public:

	void SimulateRace();

	void AssignRacerToRace(FString RacerName, int RacerID);

	void SetRaceID(int NewID);

	void UpdateOverallScore(int NewHomePts, int NewVisitorPts);

	FOnOverallScoreUpdated OnOverallScoreUpdatedDelegate;

	FOnRaceFinished OnRaceFinishedDelegate;

private:

	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_RaceNumber;

	UPROPERTY(meta = (BindWidget))
	UScoreCounter* ScoreCounter;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VB_Content;
	
	void SortArray();

	void SetRaceData();

	void CalculateRaceResult();

	void CreateRaceLines();
	
	URaceLine* CreateRaceLine(int RaceLineID);
	
	UPROPERTY(EditDefaultsOnly)
	URaceDataAsset* RaceDataAsset;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<URaceLine> RaceLineClass;
	
	TArray<URaceLine*> RaceLines;

	int ID;

	int RaceLineAmount = 4;
};

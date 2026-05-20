
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Race.generated.h"

class UPointsManager;
class URaceDataAsset;
class UNumbersBox;
class UScoreCounter;
class UTextBlock;
class URaceLine;

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

	FOnRaceFinished OnRaceFinishedDelegate;
	
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

	void SetRaceData();

	void SetRaceLinesID();

	void CalculateRaceResult();
	
	UPROPERTY(EditDefaultsOnly)
	URaceDataAsset* RaceDataAsset;
	
	TArray<URaceLine*> RaceLines;

	int ID;
};

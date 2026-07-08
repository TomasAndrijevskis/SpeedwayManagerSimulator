
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/RaceData/RaceLineData.h"
#include "Race.generated.h"

class UScoreManager;
class UNominatedRaceLine;
class URaceLine;
class URaceLineBase;
class URaceManager;
class UVerticalBox;
class UPointsManager;
class URacePatternsDataAsset;
class UNumbersBox;
class UScoreCounter;
class UTextBlock;

UCLASS()
class SMS_API URace : public UUserWidget
{
	GENERATED_BODY()

public:

	void InitializeManagers();
	
	void InitializeWidget(int NewID);

	void UpdateRacePoints();
    
	void UpdateOverallScore();
	
	FRaceLineData& GetRaceLineData(int RaceLineId) const;

	bool IsNominatedRace() const;
	
	URaceManager* GetRaceManager() const;
	
private:

	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_RaceNumber;

	UPROPERTY(meta = (BindWidget))
	UScoreCounter* ScoreCounter;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VB_Content;

	void BindDelegates();

	void CreateRaceLines();
	
	URaceLineBase* CreateRaceLine(int RaceLineID);

	URaceLineBase* CreateNominatedRaceLine(int RaceLineID);
	
	void OnIDSet();
	
	UPROPERTY(EditDefaultsOnly)
	URacePatternsDataAsset* RaceDataAsset;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<URaceLine> RaceLineClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UNominatedRaceLine> NominatedRaceLineClass;
	
	UPROPERTY()
	URaceManager* RaceManager;

	UPROPERTY()
	UScoreManager* ScoreManager;
	
	int RaceID;
};
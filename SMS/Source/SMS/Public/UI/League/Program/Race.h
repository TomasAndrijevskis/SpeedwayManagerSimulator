
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/RaceData/RaceData.h"
#include "Data/RaceData/RaceLineData.h"
#include "Race.generated.h"

class URuleBook;
class URaceLineupManager;
class UScoreManager;
class UNominatedRaceLine;
class URaceLine;
class URaceLineBase;
class URaceManager;
class UVerticalBox;
class URacePatternsDataAsset;
class UNumbersBox;
class UScoreCounter;
class UTextBlock;

UCLASS()
class SMS_API URace : public UUserWidget
{
	GENERATED_BODY()

public:
	
	void InitializeWidget(int NewID, UScoreManager* ScoreManagerRef, URuleBook* RuleBook);

	void UpdateRacePoints();
    
	void UpdateOverallScore();
	
	FRaceLineData& GetRaceLineData(int RaceLineId) const;

	bool IsNominatedRace() const;

	FRaceData& GetRaceData();
	
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

	void InitializeManagers(UScoreManager* ScoreManagerRef);

	void InitializeRaceData(URuleBook* RuleBook);
	
	UPROPERTY(EditDefaultsOnly)
	URacePatternsDataAsset* RaceDataAsset;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<URaceLine> RaceLineClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UNominatedRaceLine> NominatedRaceLineClass;

	UPROPERTY()
	TObjectPtr<UScoreManager> ScoreManager;

	FRaceData Data;
	
	int RaceID;
};
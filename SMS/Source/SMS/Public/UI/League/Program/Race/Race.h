
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/RaceData/RaceData.h"
#include "Data/RaceData/RaceLineData.h"
#include "Data/RaceData/RaceResultData.h"
#include "Race.generated.h"

class UScoreManager;
class URaceLineBase;
class URacePatternsDataAsset;
class UVerticalBox;
class UNumbersBox;
class UScoreCounter;
class UTextBlock;

DECLARE_MULTICAST_DELEGATE_OneParam(OnRaceStatsUpdateRequested, const TArray<FRaceResultData>&)
UCLASS()
class SMS_API URace : public UUserWidget
{
	GENERATED_BODY()

public:
	
	void InitializeWidget(int32 NewID, UScoreManager* ScoreManagerRef);

	void UpdateRacePoints();
    
	void UpdateOverallScore();
	
	FRaceLineData& GetRaceLineData(int32 RaceLineId) const;

	bool IsNominatedRace() const;

	FRaceData& GetRaceData();

	OnRaceStatsUpdateRequested OnRaceStatsUpdateRequestedDelegate;
	
private:

	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_RaceNumber;

	UPROPERTY(meta = (BindWidget))
	UScoreCounter* ScoreCounter;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VB_Content;

	void BindDelegates();

	void CreateRaceLines();
	
	URaceLineBase* CreateRaceLine(int32 RaceLineID);

	URaceLineBase* CreateNominatedRaceLine(int32 RaceLineID);
	
	void OnIDSet();

	void InitializeManagers(UScoreManager* ScoreManagerRef);

	void InitializeRaceData();

	void OnRaceStatsUpdateRequested(const TArray<FRaceResultData>& RaceResultData) const;
	
	UPROPERTY(EditDefaultsOnly)
	URacePatternsDataAsset* RaceDataAsset;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<URaceLineBase> RaceLineClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<URaceLineBase> NominatedRaceLineClass;

	UPROPERTY()
	TObjectPtr<UScoreManager> ScoreManager;

	FRaceData Data;
	
	int32 RaceID;
};
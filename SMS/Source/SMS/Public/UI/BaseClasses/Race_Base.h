
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/RaceData/RaceData.h"
#include "Data/RaceData/RaceLineData.h"
#include "Data/RaceData/RaceResultData.h"
#include "Race_Base.generated.h"


class URaceLine_Base;
class URacePatternsDataAsset;
class UScoreManager;
class UVerticalBox;
class UNumbersBox;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnRaceStatsUpdateRequested, const TArray<FRaceResultData>&)
UCLASS()
class SMS_API URace_Base : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void InitializeWidget(int32 NewID, UScoreManager* ScoreManagerRef);

	void OnRaceStatsUpdateRequested(const TArray<FRaceResultData>& RaceResultData) const;
	
	FRaceData& GetRaceData();

	FRaceLineData& GetRaceLineData(int32 RaceLineId) const;

	bool IsNominatedRace() const;

	void SetRacePatternDataAsset(URacePatternsDataAsset* DataAsset);
	
	FOnRaceStatsUpdateRequested OnRaceStatsUpdateRequestedDelegate;
	
protected:

	virtual void InitializeRaceData(){};
	
	virtual void BindDelegates(){};

	virtual void CreateRaceLines(){};
	
	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_RaceNumber;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VB_Content;

	UPROPERTY(EditDefaultsOnly, meta = (BlueprintBaseOnly))
	TSubclassOf<URaceLine_Base> RaceLineClass;

	UPROPERTY()
	URacePatternsDataAsset* RacePatternDataAsset;
	
	FRaceData Data;

	int32 RaceID;
	
private:

	void OnIDSet();
};


#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Race.generated.h"

class URaceManager;
class UVerticalBox;
class UPointsManager;
class URacePatternsDataAsset;
class UNumbersBox;
class UScoreCounter;
class UTextBlock;
class URaceLine;

UCLASS()
class SMS_API URace : public UUserWidget
{
	GENERATED_BODY()

public:

	void InitializeManagers();
	
	void InitializeWidget(int NewID);

	void UpdateOverallScore(int NewHomePts, int NewVisitorPts);

	const FColor& GetRequiredHelmetColor(int RaceId, int RaceLineId)const;

	int GetRacerId(int RaceId, int RaceLineId)const;

	URaceManager* GetRaceManager() const;
	
protected:

	virtual void NativeConstruct() override;
	
private:

	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_RaceNumber;

	UPROPERTY(meta = (BindWidget))
	UScoreCounter* ScoreCounter;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VB_Content;

	void BindDelegates();

	void CreateRaceLines();
	
	URaceLine* CreateRaceLine(int RaceLineID);

	void OnIDSet();
	
	void UpdateRaceScore(int NewHomePts, int NewVisitorPts);
	
	UPROPERTY(EditDefaultsOnly)
	URacePatternsDataAsset* RaceDataAsset;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<URaceLine> RaceLineClass;

	UPROPERTY()
	URaceManager* RaceManager;
	
	int RaceID;

	int RaceLineAmount = 4;
};
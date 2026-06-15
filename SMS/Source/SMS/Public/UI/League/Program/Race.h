
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

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAssignRacerRequest, const FString&, int);
DECLARE_MULTICAST_DELEGATE(FOnSimulateRaceRequest);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnRaceStatusChanged, bool)
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnScoreUpdated, int, int);
UCLASS()
class SMS_API URace : public UUserWidget
{
	GENERATED_BODY()

public:

	void InitializeManagers();
	
	void SetRaceID(int NewID);

	FOnAssignRacerRequest OnAssignRacerRequestDelegate;

	FOnSimulateRaceRequest OnSimulateRaceRequestDelegate;
	
	FOnRaceStatusChanged OnRaceStatusChangedDelegate;

	FOnScoreUpdated OnScoreUpdatedDelegate;
	
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
	
	void SetRaceData();

	void CreateRaceLines();
	
	URaceLine* CreateRaceLine(int RaceLineID);

	void OnIDSet();

	void OnRaceFinished();

	void UpdateOverallScore(int NewHomePts, int NewVisitorPts);

	void UpdateRaceScore(int NewHomePts, int NewVisitorPts);
	
	UPROPERTY(EditDefaultsOnly)
	URacePatternsDataAsset* RaceDataAsset;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<URaceLine> RaceLineClass;

	UPROPERTY()
	URaceManager* RaceManager;
	
	int ID;

	int RaceLineAmount = 4;
};
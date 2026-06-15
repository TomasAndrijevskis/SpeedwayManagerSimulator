
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
UCLASS()
class SMS_API URace : public UUserWidget
{
	GENERATED_BODY()

public:

	void InitializeManagers();
	
	void SetRaceID(int NewID);

	void UpdateOverallScore(int NewHomePts, int NewVisitorPts);

	FOnAssignRacerRequest OnAssignRacerRequestDelegate;

	FOnSimulateRaceRequest OnSimulateRaceRequestDelegate;
	
	FOnRaceStatusChanged OnRaceStatusChangedDelegate;
	
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
	
	UPROPERTY(EditDefaultsOnly)
	URacePatternsDataAsset* RaceDataAsset;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<URaceLine> RaceLineClass;

	UPROPERTY()
	URaceManager* RaceManager;
	
	int ID;

	int RaceLineAmount = 4;
};
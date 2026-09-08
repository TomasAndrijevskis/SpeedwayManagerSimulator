
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/Rules/ERaceResults.h"
#include "League_RacerStatsLine.generated.h"

class URacerMatchManager;
class UChooseBox;
class UNumbersBox;
class UTextBlock;
class UHorizontalBox;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRacerSelected, const FString&, int32);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSelectedOptionChanged, const ULeague_RacerStatsLine*, const FString&, const TObjectPtr<URacerMatchManager>&);
UCLASS()
class SMS_API ULeague_RacerStatsLine : public UUserWidget
{
	GENERATED_BODY()

public:

	void AddOption(const TObjectPtr<URacerMatchManager>& NewRacerManager);

	void RemoveOption(const FString& Option);
	
	void SetID(int32 NewID);

	int GetID() const;

	void InitializeManagers(URacerMatchManager* RacerManagerRef);

	void ChooseRandomOption(); // for testing

	void LockRacer();

	int GetNumberOfOptions() const;
	
	FOnRacerSelected OnRacerSelectedDelegate;

	FOnSelectedOptionChanged OnSelectedOptionChangedDelegate;
	
protected:

	virtual void NativeConstruct() override;
	
private:

	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_RacerNumber;
	
	UPROPERTY(meta = (BindWidget))
	UChooseBox* ChooseBox_Racer;
	
	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_OverallPoints;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HB_Points;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UNumbersBox> PointsBoxClass;

	void CreateNewPointsBox(const ERaceResults& RaceResult, bool AddBonus);

	void UpdateOverallPoints(int32 Points, int32 Bonus);

	void OnRacerChosen(FString SelectedOption, ESelectInfo::Type SelectionType);
	
	void BindDelegates();
	
	TArray<TObjectPtr<URacerMatchManager>> Racers;

	TObjectPtr<URacerMatchManager> SelectedData;
	
	int32 RacerStatsLineID;

	UPROPERTY()
	URacerMatchManager* RacerManager;

	FString PreviousOption = "";
};
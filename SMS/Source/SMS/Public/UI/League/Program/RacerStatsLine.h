
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/RacersData/RacerData.h"
#include "RacerStatsLine.generated.h"

class URacerManager;
class UChooseBox;
class UNumbersBox;
class UTextBlock;
class UHorizontalBox;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRacerSelected, const FString&, int32);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSelectedOptionChanged, const URacerStatsLine*, const FString&, FRacerData&);
UCLASS()
class SMS_API URacerStatsLine : public UUserWidget
{
	GENERATED_BODY()

public:

	void AddOption(const FRacerData Data);

	void RemoveOption(const FString& Option);
	
	void SetID(int32 NewID);

	int GetID() const;

	void InitializeManagers(URacerManager* RacerManagerRef);

	void ChooseRandomOption(); // for testing

	void LockRacer();

	int GetNumberOfOptions() const;
	
	FOnRacerSelected OnRacerSelectedDelegate;

	FOnSelectedOptionChanged OnSelectedOptionChangedDelegate;
	
protected:

	virtual void NativeConstruct() override;
	
private:

	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_RiderNumber;
	
	UPROPERTY(meta = (BindWidget))
	UChooseBox* ChooseBox_Racer;
	
	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_OverallPoints;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HB_Points;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UNumbersBox> PointsBoxClass;

	void CreateNewPointsBox(const FString& Points, bool AddBonus);

	void UpdateOverallPoints(int32 Points, int32 Bonus);

	void OnRacerChosen(FString SelectedOption, ESelectInfo::Type SelectionType);
	
	void BindDelegates();
	
	TArray<FRacerData> RacerData;

	FRacerData SelectedData;
	
	int32 RacerStatsLineID;

	UPROPERTY()
	URacerManager* RacerManager;

	FString PreviousOption = "";
};
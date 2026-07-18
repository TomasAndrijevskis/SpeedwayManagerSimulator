
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RacerStatsLine.generated.h"

class URacerManager;
class UChooseBox;
class UNumbersBox;
class UTextBlock;
class UHorizontalBox;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRacerSelected, const FString&, int);
UCLASS()
class SMS_API URacerStatsLine : public UUserWidget
{
	GENERATED_BODY()

public:

	void AddOption(const FString& NewOption);
	
	void SetID(int NewID);

	int GetID() const;

	void InitializeManagers(URacerManager* RacerManagerRef);

	void ChooseRandomOption(TArray<int>& ChosenOptions); // for testing

	void LockRacer();
	
	FOnRacerSelected OnRacerSelectedDelegate;

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

	void UpdateOverallPoints(int Points, int Bonus);

	void OnRacerChosen(FString SelectedItem, ESelectInfo::Type SelectionType);
	
	void BindDelegates();

	UPROPERTY()
	int RacerStatsLineID;

	UPROPERTY()
	URacerManager* RacerManager;
};
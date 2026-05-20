
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RacerStatsLine.generated.h"

class UChooseBox;
class UNumbersBox;
class UTextBlock;
class UHorizontalBox;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnValueAddRequest, const FString&)
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRacerChosen, FString, int);
UCLASS()
class SMS_API URacerStatsLine : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetID(int NewID);

	int GetID() const;

	FString GetRacerName() const;

	FOnValueAddRequest OnValueAddRequestDelegate;

	FOnRacerChosen OnRacerChosenDelegate;
	
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

	void CreateNewPointsBox(const FString& Points);

	void UpdateOverallPoints(int Points);

	int CountOverallPoints();

	bool CanAddNewPointBox() const;

	void OnRacerChosen(FString SelectedItem, ESelectInfo::Type SelectionType);

	void AddPoints(const FString& NewPoints);
	
	UPROPERTY(VisibleAnywhere)
	TArray<FString> RacerPoints;

	UPROPERTY(EditDefaultsOnly)
	int MaxRacesAmount = 7;

	UPROPERTY(VisibleAnywhere)
	int ID;

	UPROPERTY(VisibleAnywhere)
	FString RacerName;
};
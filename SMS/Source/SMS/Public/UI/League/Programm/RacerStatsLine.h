
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RacerStatsLine.generated.h"

class UNamesBox;
class UNumbersBox;
class UTextBlock;
class UHorizontalBox;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnValueAdded, const FString&)
UCLASS()
class SMS_API URacerStatsLine : public UUserWidget
{
	GENERATED_BODY()

public:
	
	FOnValueAdded OnValueAddedDelegate;

	UFUNCTION(BlueprintCallable)
	void AddPoints();
	
protected:

	virtual void NativeConstruct() override;
	
private:

	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_RiderNumber;
	
	UPROPERTY(meta = (BindWidget))
	UNamesBox* NamesBox_RacerName;

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
	
	UPROPERTY(VisibleAnywhere)
	TArray<FString> RacerPoints;

	UPROPERTY(EditDefaultsOnly)
	int MaxRacesAmount = 7;
};


#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RaceLine.generated.h"


class UChooseBox;
class UNumbersBox;
class UNamesBox;
class UOverlay;
class USlider;
class UTextBlock;
class UHorizontalBox;

UCLASS()
class SMS_API URaceLine : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetRider(const FColor& NewHelmetColour, const FString& NewRacerName, const FString& NewRacerNumber);

	void SetPoints(int NewPoints);

	void ChangeRider();

	UFUNCTION()
	void OnRacerReplaced(FString SelectedItem, ESelectInfo::Type SelectionType);
	
protected:

	virtual void NativeConstruct() override;
	
private:

	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_RacerNumber;

	UPROPERTY(meta = (BindWidget))
	UOverlay* Overlay_RacerName;
	
	UPROPERTY(meta = (BindWidget))
	UNamesBox* NamesBox_RacerName;

	UPROPERTY(meta = (BindWidget))
	UChooseBox* ChooseBox_RacerReplacement;

	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_PointsPerRace;
	
	USlider* CreateSlider();

	UPROPERTY(EditAnywhere)
	FColor HelmetColour;
	UPROPERTY(EditAnywhere)
	FString RacerName;
	UPROPERTY(EditAnywhere)
	FString RacerNumber;
	
};

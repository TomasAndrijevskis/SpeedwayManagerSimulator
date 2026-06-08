
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RaceLine.generated.h"


class UMatchManager;
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
	
	void SetRacerName(const FString& NewRacerName);
	
	void SetPoints(int NewPoints);

	void ChangeRider();

	UFUNCTION()
	void OnRacerReplaced(FString SelectedItem, ESelectInfo::Type SelectionType);

	void GenerateRandomNumber();

	int GetGeneratedNumber() const;

	int GetRaceLineID() const;

	int GetRacerID() const;

	int GetPoints() const;
	
	void SetRaceLineID(int NewID);

	void SetRacerID(int NewID);
	
	void SetRacerValues(const FColor& NewHelmetColour, int NewRacerID);

	void SetIsVisitor(bool Visitor);

	bool GetIsVisitor() const;
	
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

	UPROPERTY()
	UMatchManager* MatchManager;
	
	int RandomNumber = 0;
	
	int RaceLineID;

	int RacerID;
	
	bool IsVisitor;

	int Points = 0;
};
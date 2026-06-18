
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/RacersData/RacerData.h"
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

	void SetRacerData(const FRacerData& NewRacerData);

	void ChangeRider();

	UFUNCTION()
	void OnRacerReplaced(FString SelectedItem, ESelectInfo::Type SelectionType);

	void CalculateRating();

	int GetRaceLineID() const;

	int GetRacerID() const;

	int GetPointsPerRace() const;

	void SetPointsPerRace(int NewPoints);
	
	void SetRaceLineID(int NewID);

	void SetRacerID(int NewID);
	
	void SetRaceLineData(const FColor& NewHelmetColour, int NewRacerID);

	bool GetIsVisitor() const;

	int GetRacerRating() const;

	void OnRaceFinished();
	
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

	void SetRacerName(const FString& NewRacerName);
	
	UPROPERTY()
	UMatchManager* MatchManager;

	FRacerData RacerData;
	
	int RaceLineID;

	int RacerID;

	int Points = 0;

	int CurrentRacerRating = 0;
};
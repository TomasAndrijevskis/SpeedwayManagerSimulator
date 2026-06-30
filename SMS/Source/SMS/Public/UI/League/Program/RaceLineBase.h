
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/RaceData/RaceLineData.h"
#include "Data/RacersData/RacerData.h"
#include "RaceLineBase.generated.h"


class USlider;
class UChooseBox;
class UOverlay;
class UNumbersBox;

DECLARE_MULTICAST_DELEGATE(FOnRaceStarted);
UCLASS()
class SMS_API URaceLineBase : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetRaceLineID(int NewID);
	int GetRaceLineID() const;
	
	void SetRacerID(int NewRacerID);
	int GetRacerID() const;

	void SetPointsPerRace(int NewPoints);
	int GetPointsPerRace() const;
	
	int GetRacerRating() const;
	
	int GetTieBreaker() const;

	bool IsVisitor() const;
	
	void SetRaceLineData(const FRaceLineData& NewRaceLineData);

	void SetRacerData(const FRacerData& NewRacerData);

	void ChangeRider();

	UFUNCTION()
	void OnRacerReplaced(FString SelectedItem, ESelectInfo::Type SelectionType);
	
	void OnRaceFinished();
	
	FOnRaceStarted OnRaceStartedDelegate;
	
protected:

	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_RacerNumber;

	UPROPERTY(meta = (BindWidget))
	UOverlay* Overlay_RacerName;
	
	UPROPERTY(meta = (BindWidget))
	UChooseBox* ChooseBox_RacerReplacement;

	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_PointsPerRace;

	virtual void NativeConstruct() override;
	
	UPROPERTY()
	URacerManager* RacerManager;
	
	FRacerData RacerData;

	FRaceLineData RaceLineData;
	
private:

	void BindDelegates();

	USlider* CreateSlider();

	int RaceLineID = 0;

	int RacerID = 0;

	int Points = 0;

	bool bIsVisitor = false;
};
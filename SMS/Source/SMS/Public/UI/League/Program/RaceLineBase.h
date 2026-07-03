
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/RaceData/RaceLineData.h"
#include "Data/RacersData/RacerMatchData.h"
#include "RaceLineBase.generated.h"


struct FRacerMatchData;
class URacerManager;
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
	
	void SetPointsPerRace(const FString& NewPoints, bool AddBonus);
	int GetPointsPerRace() const;
	
	int GetRacerRating() const;
	
	int GetTieBreaker() const;
	
	virtual void SetRaceLineData(const FRaceLineData& NewRaceLineData);

	void SetRacerData(const FRacerMatchData& NewRacerData, URacerManager* RacerManagerRef);

	bool IsVisitor() const;
	
	void ChangeRider();

	UFUNCTION()
	void OnRacerReplaced(FString SelectedItem, ESelectInfo::Type SelectionType);
	
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

	virtual void SetRacerName(const FString& NewRacerName){};
	
	UPROPERTY()
	URacerManager* RacerManager;
	
	FRacerMatchData RacerData;

	FRaceLineData RaceLineData;
	
private:

	void BindManagerDelegates();

	void BindDelegates();
	
	void OnRaceStarted();

	USlider* CreateSlider();
	
	int RaceLineID = 0;

	int RacerID = 0;
};
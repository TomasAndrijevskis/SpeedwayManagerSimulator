
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/RaceData/RaceLineData.h"
#include "RaceLineBase.generated.h"


class UTeamManager;
class URacerManager;
class USlider;
class UChooseBox;
class UOverlay;
class UNumbersBox;

DECLARE_MULTICAST_DELEGATE(FOnRaceStarted);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRacerReplaced, URaceLineBase*, const FString&);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRacerChosen, URaceLineBase*, const FString&);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSelectedRacerChanged, URaceLineBase*, URacerManager*);
UCLASS()
class SMS_API URaceLineBase : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetRaceLineID(int32 NewID);
	int32 GetRaceLineID() const;
	
	void SetRacerNumber(int32 NewRacerNumber);
	int32 GetRacerNumber() const;
	
	void SetPointsPerRace(const FString& NewPoints, bool AddBonus);
	int32 GetPointsPerRace() const;
	
	int32 GetRacerRating() const;
	
	int32 GetTieBreaker() const;
	
	virtual void SetRaceLineData(const FRaceLineData& NewRaceLineData);

	void SetRacerData(URacerManager* RacerManagerRef, bool IsReplacement);
	
	void CrossOutRacer();

	void ChangeLineStatus(bool bIsActive);
	
	int32 GetTeamID() const;

	void AddReplacementOption(FString SelectedItem);
	virtual void AddMainOption(FString SelectedItem){};
	void RemoveFromReplacementSelection(FString SelectedItem);
	virtual void RemoveFromMainSelection(FString SelectedItem){};
	
	void ChangeChooseBoxStatus(bool Status);
	
	URacerManager* GetRacerManager() const;
	
	UTeamManager* GetTeamManager() const;

	FRaceLineData& GetRaceLineData();

	bool IsRacerSet() const;
	
	FOnRaceStarted OnRaceStartedDelegate;

	FOnRacerReplaced OnRacerReplacedDelegate;

	FOnRacerChosen OnRacerChosenDelegate;
	
	FOnSelectedRacerChanged OnSelectedRacerChangedDelegate;
	
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

	virtual void NativeConstruct() override;

	void InitializeWidget();
	
	virtual void BindDelegates();

	UFUNCTION()
	virtual void OnRacerChosen(FString SelectedItem, ESelectInfo::Type SelectionType){};

	UFUNCTION()
	virtual void OnRacerReplaced(FString SelectedItem, ESelectInfo::Type SelectionType);
	
	FRaceLineData RaceLineData;

	UPROPERTY()
	UTeamManager* TeamManager;

	UPROPERTY()
	URacerManager* RacerManager;
	
private:

	void BindManagerDelegates();

	USlider* CreateSlider();

	void SetTeamManager(TArray<UTeamManager*> TeamManagersRef);
	
	int32 RaceLineID = 0;

	int32 RacerNumber = 0;

	bool bIsRacerSet = false;
};
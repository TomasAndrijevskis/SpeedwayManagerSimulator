
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/RaceData/RaceLineData.h"
#include "Data/RacersData/RacerMatchData.h"
#include "RaceLineBase.generated.h"


class UTeamManager;
class UMatchManager;
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
	
	int GetRacerNumber() const;
	
	void SetPointsPerRace(const FString& NewPoints, bool AddBonus);
	int GetPointsPerRace() const;
	
	int GetRacerRating() const;
	
	int GetTieBreaker() const;
	
	virtual void SetRaceLineData(const FRaceLineData& NewRaceLineData);

	void SetRacerData(const FRacerMatchData& NewRacerData, URacerManager* RacerManagerRef);

	bool IsVisitor() const;
	
	void ChangeRider();

	void HandleRace(bool bIsActive);
	
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

	virtual void NativeConstruct() override;

	virtual void InitializeWidget();

	virtual void AddOption(const FRacerMatchData& Data, URacerManager* NewRacerManager);

	virtual void BindDelegates();

	UFUNCTION()
	void OnRacerChosen(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnRacerReplaced(FString SelectedItem, ESelectInfo::Type SelectionType);
	
	FRacerMatchData RacerData;

	FRaceLineData RaceLineData;

	UPROPERTY()
	UTeamManager* TeamManager;

	UPROPERTY()
	URacerManager* RacerManager;

	UPROPERTY()
	TMap<URacerManager*, FRacerMatchData> RacerManagers;

	bool IsReplacement = false;
	
private:

	void BindManagerDelegates();
	
	void OnRaceStarted();

	USlider* CreateSlider();

	void SetTeamManager(TArray<UTeamManager*> TeamManagersRef);

	void SetRacerNumber(int NewRacerNumber);

	void FindSelectedRacer(const FString& SelectedItem, const TFunction<void(URacerManager*, const FRacerMatchData&)>& Callback);

	void FillOptions();
	
	int RaceLineID = 0;

	int RacerNumber = 0;
};
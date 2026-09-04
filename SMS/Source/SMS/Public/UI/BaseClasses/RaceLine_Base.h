
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/RaceData/RaceLineData.h"
#include "Data/Track/ETrackTypes.h"
#include "RaceLine_Base.generated.h"


class URacerManager;
class UNumbersBox;

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnRaceSimulated, float, float, ETrackTypes);
UCLASS()
class SMS_API URaceLine_Base : public UUserWidget
{
	GENERATED_BODY()

public:

	void ChangeLineStatus(bool bIsActive);
	
	virtual void SetRaceLineData(const FRaceLineData& NewRaceLineData);
	FRaceLineData& GetRaceLineData();
	
	void SetRaceLineID(int32 NewID);
	int32 GetRaceLineID() const;

	void SetRacerNumber(int32 NewRacerNumber);
	int32 GetRacerNumber() const;

	void SetPointsPerRace(const FString& NewPoints);
	int32 GetPointsPerRace() const;

	int32 GetRacerRating() const;
	
	int32 GetTieBreaker() const;
	
	URacerManager* GetRacerManager() const;

	bool IsRacerSet() const;

	FOnRaceSimulated OnRaceSimulatedDelegate;
	
protected:

	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_RacerNumber;
	
	virtual void NativeConstruct() override;
	
	virtual void SetRacerName(const FString& NewRacerName){};
	
	virtual void InitializeWidget() {};
	
	virtual void BindDelegates() {};

	void BindManagersDelegates();
	
	UPROPERTY()
	URacerManager* RacerManager;

	FRaceLineData RaceLineData;

	bool bIsRacerSet = false;
	
private:

	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_PointsPerRace;
	
	int32 RaceLineID = 0;

	int32 RacerNumber = 0;
	
};

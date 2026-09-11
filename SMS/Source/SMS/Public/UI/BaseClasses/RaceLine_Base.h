
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/RaceData/RaceLineData.h"
#include "Data/Track/ETrackTypes.h"
#include "RaceLine_Base.generated.h"


class URacerMatchManager;
class UNumbersBox;

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnRaceSimulated, float, float, ETrackTypes);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRacerSet, URacerMatchManager*, int32);
DECLARE_DELEGATE_RetVal_OneParam(FString, FRequestRaceLinePoints, int32);
UCLASS()
class SMS_API URaceLine_Base : public UUserWidget
{
	GENERATED_BODY()

public:

	void ChangeLineStatus(bool bIsActive);

	void OnRaceFinished();
	
	virtual void SetRaceLineData(const FRaceLineData& NewRaceLineData);
	
	void SetIDs(int32 NewRaceLineID, int32 NewRaceID);
	int32 GetRaceLineID() const;
	int32 GetRaceID() const;
	
	void SetRacerNumber(int32 NewRacerNumber);
	int32 GetRacerNumber() const;

	void SetPointsPerRace(const FString& NewPoints);
	int32 GetPointsPerRace() const;
	
	URacerMatchManager* GetRacerManager() const;

	FOnRaceSimulated OnRaceSimulatedDelegate;

	FOnRacerSet OnRacerSetDelegate;

	FRequestRaceLinePoints OnRequestRaceLinePointsDelegate;
	
protected:

	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_RacerNumber;
	
	virtual void NativeConstruct() override;
	
	virtual void SetRacerName(const FString& NewRacerName){};
	
	virtual void InitializeWidget() {};
	
	virtual void BindDelegates() {};
	
	UPROPERTY()
	URacerMatchManager* RacerManager;

	FRaceLineData RaceLineData;

	int32 RaceLineID = 0;

	int32 RaceID = 0;
	
	int32 RacerNumber = 0;
	
private:

	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_PointsPerRace;
	
};

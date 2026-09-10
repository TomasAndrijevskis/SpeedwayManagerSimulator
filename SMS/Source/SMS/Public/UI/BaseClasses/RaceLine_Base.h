
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/RaceData/RaceLineData.h"
#include "Data/Track/ETrackTypes.h"
#include "RaceLine_Base.generated.h"


class URacerMatchManager;
class UNumbersBox;

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnRaceSimulated, float, float, ETrackTypes);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnRacerSet, URacerMatchManager*);
UCLASS()
class SMS_API URaceLine_Base : public UUserWidget
{
	GENERATED_BODY()

public:

	void ChangeLineStatus(bool bIsActive);
	
	virtual void SetRaceLineData(const FRaceLineData& NewRaceLineData);
	
	void SetRaceLineID(int32 NewID);
	int32 GetRaceLineID() const;

	void SetRacerNumber(int32 NewRacerNumber);
	int32 GetRacerNumber() const;

	void SetPointsPerRace(const FString& NewPoints);
	int32 GetPointsPerRace() const;
	
	URacerMatchManager* GetRacerManager() const;

	FOnRaceSimulated OnRaceSimulatedDelegate;

	FOnRacerSet OnRacerSetDelegate;
	
protected:

	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_RacerNumber;
	
	virtual void NativeConstruct() override;
	
	virtual void SetRacerName(const FString& NewRacerName){};
	
	virtual void InitializeWidget() {};
	
	virtual void BindDelegates() {};

	void BindManagersDelegates();
	
	UPROPERTY()
	URacerMatchManager* RacerManager;

	FRaceLineData RaceLineData;
	
private:

	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_PointsPerRace;
	
	int32 RaceLineID = 0;

	int32 RacerNumber = 0;
	
};

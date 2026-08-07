
#pragma once

#include "CoreMinimal.h"
#include "Data/RaceData/RaceResultData.h"
#include "RaceManager.generated.h"

class URaceLineBase;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRaceScoreUpdated, int32, int32);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnOverallScoreUpdated, int32, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnChangeRaceStatusRequest, bool);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnRaceLineResultUpdated, const TArray<FRaceResultData>&)
DECLARE_MULTICAST_DELEGATE(FOnSimulateRaceRequest);
DECLARE_MULTICAST_DELEGATE(FOnRaceFinished);
UCLASS()
class SMS_API URaceManager : public UObject
{
	GENERATED_BODY()

public:

	void InitializeManager(bool NewIsNominatedRace);
	
	void AddRaceLine(URaceLineBase* NewRaceLine);
	
	void ChangeRaceStatus(bool bIsActive);

	void BindDelegates();

	bool IsNominatedRace() const;

	bool CheckAllRacersInRace() const;
	
	FOnRaceScoreUpdated OnRaceScoreUpdatedDelegate;

	FOnChangeRaceStatusRequest OnChangedRaceStatusRequestDelegate;

	FOnSimulateRaceRequest OnSimulateRaceRequestDelegate;

	FOnOverallScoreUpdated OnOverallScoreUpdatedDelegate;

	FOnRaceFinished OnRaceFinishedDelegate;

	FOnRaceLineResultUpdated OnRaceLineResultUpdatedDelegate;
	
private:
	
	void SortLinesByRating();

	void SimulateRace();

	void OnRaceFinished();

	void BroadcastRaceResult();
	
	UPROPERTY()
	TArray<URaceLineBase*> RaceLines;
	
	const FString DidNotFinish = TEXT("D");

	bool bIsNominatedRace = false;

	TArray<FRaceResultData> RaceResults;
};
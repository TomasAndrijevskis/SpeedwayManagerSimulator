
#pragma once

#include "CoreMinimal.h"
#include "UI/League/Program/RaceLine.h"
#include "RaceManager.generated.h"

class URaceLineupManager;
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRaceScoreUpdated, int, int);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnOverallScoreUpdated, int, int);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnChangeRaceStatusRequest, bool)
DECLARE_MULTICAST_DELEGATE(FOnSimulateRaceRequest);
DECLARE_MULTICAST_DELEGATE(FOnRaceFinished);
UCLASS()
class SMS_API URaceManager : public UObject
{
	GENERATED_BODY()

public:

	void InitializeManager();
	
	void AddRaceLine(URaceLineBase* NewRaceLine);
	
	void ChangeRaceStatus(bool bIsActive);
	
	TArray<URaceLineBase*> GetRaceLines();

	void BindDelegates();

	void OnRaceLinesCreated() const;
	
	URaceLineupManager* GetRaceLineupManager() const;
	
	FOnRaceScoreUpdated OnRaceScoreUpdatedDelegate;

	FOnChangeRaceStatusRequest OnChangedRaceStatusRequestDelegate;

	FOnSimulateRaceRequest OnSimulateRaceRequestDelegate;

	FOnOverallScoreUpdated OnOverallScoreUpdatedDelegate;

	FOnRaceFinished OnRaceFinishedDelegate;
	
private:
	
	void SortLinesByRating();

	void SimulateRace();

	void OnRaceFinished();

	void BroadcastRaceResult();
	
	UPROPERTY()
	TArray<URaceLineBase*> RaceLines;

	UPROPERTY()
	URaceLineupManager* RaceLineupManager;
	
	const FString DidNotFinish = TEXT("D");
};
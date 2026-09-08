
#pragma once

#include "CoreMinimal.h"
#include "Data/RaceData/RaceResultData.h"
#include "RaceManager.generated.h"

class ULeague_RaceLine_Base;
class UTrackManager;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRaceScoreUpdated, bool, int32);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnOverallScoreUpdated, int32, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnChangeRaceStatusRequest, bool);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnRaceLineResultUpdated, const TArray<FRaceResultData>&)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnSimulateRaceRequest, const TObjectPtr<UTrackManager>&);
DECLARE_MULTICAST_DELEGATE(FOnRaceFinished);
UCLASS()
class SMS_API URaceManager : public UObject
{
	GENERATED_BODY()

public:

	void InitializeManager(bool NewIsNominatedRace, int32 NewRaceID);
	
	void InitializeManager();
	
	void AddRaceLine(ULeague_RaceLine_Base* NewRaceLine);
	
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

	void SimulateRace(const TObjectPtr<UTrackManager>& TrackManager);

	void OnRaceFinished();

	void BroadcastRaceResult();
	
	UPROPERTY()
	TArray<ULeague_RaceLine_Base*> RaceLines;

	bool bIsNominatedRace = false;

	TArray<FRaceResultData> RaceResults;

	int32 RaceID = 0;
};
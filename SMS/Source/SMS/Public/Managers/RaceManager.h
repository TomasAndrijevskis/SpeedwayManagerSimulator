
#pragma once

#include "CoreMinimal.h"
#include "Data/RaceData/RaceResultData.h"
#include "RaceManager.generated.h"

class URacerMatchManager;
class ULeague_RaceLine_Base;
class UTrackManager;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRaceScoreUpdated, bool, int32);
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

	void InitializeManager(bool NewIsNominatedRace, int32 NewRaceID);
	
	void InitializeManager();

	void BindDelegates();

	bool IsNominatedRace() const;

	void AddRacerManager(URacerMatchManager* NewRacerMatchManager);

	void RemoveRacerManager(URacerMatchManager* NewRacerMatchManager);

	bool AreAllRacersSet();
	
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
	TArray<URacerMatchManager*> RacerMatchManagers;
	
	bool bIsNominatedRace = false;

	TArray<FRaceResultData> RaceResults;
	
	int32 RaceID = 0;
};
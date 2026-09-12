
#pragma once

#include "CoreMinimal.h"
#include "Data/RaceData/RaceLineResultData.h"
#include "Data/RaceData/RaceResultData.h"
#include "Data/Rules/ERaceResults.h"
#include "RaceManager.generated.h"

class URulesSubsystem;
class URacerMatchManager;
class ULeague_RaceLine_Base;
class UTrackManager;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRaceScoreUpdated, bool, int32);
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

	void AddRacerManager(URacerMatchManager* NewRacerMatchManager, int32 RaceLineID);

	void RemoveRacerManager(int32 RaceLineID);

	bool AreAllRacersSet();

	FString GetRaceLinePoints(int32 RaceLineID);
	
	FOnRaceScoreUpdated OnRaceScoreUpdatedDelegate;

	FOnChangeRaceStatusRequest OnChangedRaceStatusRequestDelegate;

	FOnSimulateRaceRequest OnSimulateRaceRequestDelegate;

	FOnRaceFinished OnRaceFinishedDelegate;

	FOnRaceLineResultUpdated OnRaceLineResultUpdatedDelegate;
	
private:
	
	void SortLinesByRating();

	void SimulateRace();
	
	void OnRaceFinished();

	void BroadcastRaceResult(TArray<FRaceLineResultData>& ResultForEachLine);

	void CalculateRacerRatings();

	bool AreRacersFromSameTeam(int32 Position, const TObjectPtr<URacerMatchManager>& PreviousManager, bool IsCurrentRacerVisitor);

	void CollectRaceLineData(ERaceResults Result, bool IsCurrentRacerVisitor, const URulesSubsystem& RulesSubsystem, TArray<FRaceLineResultData>& OutArray);

	void CollectRaceResults(ERaceResults Result, int32 RaceLineID, const URulesSubsystem& RulesSubsystem);
	
	UPROPERTY()
	TMap<int32, URacerMatchManager*> Racers;
	
	bool bIsNominatedRace = false;

	TArray<FRaceResultData> RaceResults;
	
	int32 RaceID = 0;
};
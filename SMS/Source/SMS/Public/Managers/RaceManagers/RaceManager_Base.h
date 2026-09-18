
#pragma once

#include "CoreMinimal.h"
#include "Data/RaceData/RaceResultData.h"
#include "Data/Rules/ERaceResults.h"
#include "RaceManager_Base.generated.h"

class URulesSubsystem;
class URacerMatchManager;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRaceScoreUpdated, bool, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnChangeRaceStatus, bool);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnRaceLineResultUpdated, const TArray<FRaceResultData>&)
DECLARE_MULTICAST_DELEGATE(FOnSimulateRace);
DECLARE_MULTICAST_DELEGATE(FOnRaceFinished);
UCLASS()
class SMS_API URaceManager_Base : public UObject
{
	GENERATED_BODY()

public:

	void InitializeManager(bool NewIsNominatedRace, int32 NewRaceID);
	
	void BindDelegates();

	void AddRacerManager(URacerMatchManager* NewRacerMatchManager, int32 RaceLineID);
	
	bool AreAllRacersSet();

	FString GetRaceLinePoints(int32 RaceLineID);
	
	int32 GetRaceID() const {return RaceID;};
	
	bool IsNominatedRace() const {return bIsNominatedRace;};
	
	FOnRaceScoreUpdated OnRaceScoreUpdatedDelegate;

	FOnChangeRaceStatus OnChangedRaceStatusDelegate;

	FOnSimulateRace OnSimulateRaceDelegate;

	FOnRaceFinished OnRaceFinishedDelegate;

	FOnRaceLineResultUpdated OnRaceLineResultUpdatedDelegate;

protected:

	void SortLinesByRating();

	void ApplyRacerResult(URacerMatchManager& Racer, ERaceResults& Result, bool HasBonus);
	
	void CalculateRacerRatings();
	
	void OnRaceFinished();

	void CollectRaceResults(ERaceResults Result, int32 RaceLineID, const URulesSubsystem& RulesSubsystem);
	
	UPROPERTY()
	TMap<int32, URacerMatchManager*> Racers;

	UPROPERTY()
	TArray<FRaceResultData> RaceResults;
	
	int32 RaceID = 0;
	
private:

	virtual void SimulateRace() {};
	
	bool bIsNominatedRace = false;
};
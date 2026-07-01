
#pragma once

#include "CoreMinimal.h"
#include "Data/RacersData/RacerMatchData.h"
#include "UI/League/Program/RaceLine.h"
#include "RaceManager.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnRaceFinished);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRaceScoreUpdated, int, int);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnOverallScoreUpdated, int, int);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnRaceStatusChanged, bool)
DECLARE_MULTICAST_DELEGATE(FOnSimulateRaceRequest);
UCLASS()
class SMS_API URaceManager : public UObject
{
	GENERATED_BODY()

public:

	void AddRaceLine(URaceLineBase* NewRaceLine);

	void AssignRacerToRace(const FRacerMatchData& RacerData, URacerManager* RacerManagerRef);
	
	void ChangeRaceStatus(bool bIsActive);
	
	TArray<URaceLineBase*> GetRaceLines();

	void CalculateRaceResult();

	void BindDelegates();
	
	void UpdateOverallScore(int HomePts, int VisitorPts);
	
	FOnRaceFinished OnRaceFinishedDelegate;

	FOnRaceScoreUpdated OnRaceScoreUpdatedDelegate;

	FOnRaceStatusChanged OnRaceStatusChangedDelegate;

	FOnSimulateRaceRequest OnSimulateRaceRequestDelegate;

	FOnOverallScoreUpdated OnOverallScoreUpdatedDelegate;
	
private:
	
	void SortLinesByRating();

	void SimulateRace();
	
	UPROPERTY()
	TArray<URaceLineBase*> RaceLines;
	
};

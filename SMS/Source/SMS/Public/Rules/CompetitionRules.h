
#pragma once

#include "CoreMinimal.h"
#include "Data/RaceData/RaceData.h"
#include "Data/Rules/ERaceResults.h"
#include "Data/Track/TrackData.h"
#include "CompetitionRules.generated.h"


class URacerMatchManager;
class UTrackManager;

DECLARE_MULTICAST_DELEGATE(FOnRacingFinished);
DECLARE_MULTICAST_DELEGATE(FOnMatchClosed);
DECLARE_MULTICAST_DELEGATE(FOnRaceStarted);
UCLASS(Abstract)
class SMS_API UCompetitionRules : public UObject
{
	GENERATED_BODY()
	
public:

	virtual void SetupMatch() PURE_VIRTUAL(UCompetitionRules::SetupMatch);
	
	virtual bool CanStartMatch() const PURE_VIRTUAL(UCompetitionRules::CanStartMatch, return false;);

	virtual void PopulateRacers() PURE_VIRTUAL(UCompetitionRules::PopulateRacers);
	
	virtual void CollectRacerStatistics() PURE_VIRTUAL(UCompetitionRules::CollectRacerStatistics);

	virtual void PrepareToEndMatch() PURE_VIRTUAL(UCompetitionRules::PrepareToEndMatch);

	virtual void MakeRandomRosters() PURE_VIRTUAL(UCompetitionRules::MakeRandomRosters);

	virtual void InitializeRules() PURE_VIRTUAL(UCompetitionRules::InitializeRules)
	
	void EndMatch();
	
	void AddNewRace(int32 RaceId, FRaceData RaceData);

	void RequestToAssignRacersToRace(URacerMatchManager* RacerManager);

	FString GetRaceResultText(const ERaceResults RaceResult) const;

	int32 GetRaceResultAsNumber(const ERaceResults RaceResult) const;
	
	int32 GetCurrentRaceNumber() const {return CurrentRace;}

	int32 GetAmountOfRaces() const {return Races.Num();}
	
	TObjectPtr<UTrackManager>& GetTrackManager() {return TrackManager;}

	bool IsTrackCleaningTime() const {return TrackCleaningRaces.Contains(CurrentRace);}
	
	FOnRacingFinished OnRacingFinishedDelegate;

	FOnMatchClosed OnMatchClosedDelegate;
	
	FOnRaceStarted OnRaceStartedDelegate;

protected:

	virtual void HandleRaceFinished();

	virtual void HandleMatchClosed();
	
	void CreateTrackManager(const FTrackData& TrackData);
	
	void BindDelegates();
	
	UPROPERTY()
	TMap<int32, FRaceData> Races;

	UPROPERTY()
	TArray<int32> TrackCleaningRaces {};
	
	int32 CurrentRace = 1;

private:
	
	void SimulateRace();
	
	UPROPERTY()
	TObjectPtr<UTrackManager> TrackManager;
};


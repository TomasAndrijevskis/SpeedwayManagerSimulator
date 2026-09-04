
#pragma once

#include "CoreMinimal.h"
#include "Data/RaceData/RaceData.h"
#include "Data/Track/TrackData.h"
#include "CompetitionRules.generated.h"


class URacerManager;
class UTrackManager;

DECLARE_MULTICAST_DELEGATE(FOnMatchEnded);
DECLARE_MULTICAST_DELEGATE(FOnRaceStarted);
UCLASS(Abstract)
class SMS_API UCompetitionRules : public UObject
{
	GENERATED_BODY()
	
public:

	virtual void SetupMatch() PURE_VIRTUAL(UCompetitionRules::SetupMatch);

	virtual void BindRaceDelegates() PURE_VIRTUAL(UCompetitionRules::BindRaceDelegates);
	
	void AddNewRace(int32 RaceId, FRaceData RaceData);

	void RequestToAssignRacersToRace(URacerManager* RacerManager);

	int32 GetCurrentRaceNumber()const;

	int32 GetAmountOfRaces() const;
	
	FOnMatchEnded OnMatchEndedDelegate;
	
	FOnRaceStarted OnRaceStartedDelegate;

protected:

	virtual void HandleRaceFinished();
	
	void CreateTrackManager(const FTrackData& HomeTeamTrackData);
	
	void BindDelegates();
	
	UPROPERTY()
	TMap<int32, FRaceData> Races;

	int32 CurrentRace = 1;
	
private:
	
	void SimulateRace();
	
	UPROPERTY()
	TObjectPtr<UTrackManager> TrackManager;
	
};


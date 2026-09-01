
#pragma once

#include "CoreMinimal.h"
#include "Data/RaceData/RaceData.h"
#include "Data/TeamData/TeamMatchData.h"
#include "MatchManager.generated.h"

class UTrackManager;
class URacerManager;
class UTeamManager;
class UScoreManager;
class ASMS_GameMode;

DECLARE_MULTICAST_DELEGATE(FOnMatchEnded);
DECLARE_MULTICAST_DELEGATE(FOnRaceStared);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnRacerManagersCreated, TArray<UTeamManager*>);
UCLASS()
class SMS_API UMatchManager : public UObject
{
	GENERATED_BODY()

public:

	void AddNewRace(int32 RaceId, FRaceData RaceData);
	
	void RequestToAssignRacersToRace(URacerManager* RacerManager);
	
	void InitializeManager(ASMS_GameMode* CurrentGameMode);
	
	void SetTeam(ETeams NewTeam, bool IsVisitor);

	int32 GetCurrentRaceNumber()const;

	int32 GetAmountOfRaces() const;

	void CreateRacerManagers(TArray<UTeamManager*> TeamManagersRef);

	FTeamMatchData* GetTeamData(bool Status);

	UScoreManager* GetScoreManager() const;
	
	FOnMatchEnded OnMatchEndedDelegate;
	
	FOnRaceStared OnRaceStaredDelegate;

	FOnRacerManagersCreated OnRacerManagersCreatedDelegate;
	
private:

	void BindRaceDelegates();

	void BindDelegates();
	
	void HandleRaceFinished();
	
	void SimulateRace();

	void PopulateRacers(TArray<UTeamManager*> TeamManagersRef);

	void CreateTrackManager(const FTrackData& HomeTeamTrackData);
	
	UPROPERTY()
	ASMS_GameMode* GameMode;

	UPROPERTY()
	TObjectPtr<UScoreManager> ScoreManager;

	UPROPERTY()
	TObjectPtr<UTrackManager> TrackManager;
	
	UPROPERTY()
	TMap<int32, FRaceData> Races;
	
	TArray<FTeamMatchData> Teams;
	
	int32 CurrentRace = 1;
};
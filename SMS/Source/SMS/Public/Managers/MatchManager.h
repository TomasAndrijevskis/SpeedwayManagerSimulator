
#pragma once

#include "CoreMinimal.h"
#include "Data/RaceData/RaceData.h"
#include "Data/TeamData/TeamMatchData.h"
#include "UI/League/Program/Race.h"
#include "MatchManager.generated.h"

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

	void AddNewRace(int RaceId, FRaceData RaceData);
	
	void RequestToAssignRacersToRace(URacerManager* RacerManager);
	
	void InitializeManager(ASMS_GameMode* CurrentGameMode);
	
	void SetTeamID(int NewTeamID, bool IsVisitor);

	int GetCurrentRaceNumber()const;

	int GetAmountOfRaces() const;

	void CreateRacerManagers(TArray<UTeamManager*> TeamManagersRef);

	FTeamMatchData* GetTeamData(bool Status);

	FOnMatchEnded OnMatchEndedDelegate;
	
	FOnRaceStared OnRaceStaredDelegate;

	FOnRacerManagersCreated OnRacerManagersCreatedDelegate;
	
private:

	void BindRaceDelegates();

	void BindDelegates();
	
	void HandleRaceFinished();
	
	void SimulateRace();

	void PopulateRacers(TArray<UTeamManager*> TeamManagersRef);
	
	UPROPERTY()
	ASMS_GameMode* GameMode;

	UPROPERTY()
	UScoreManager* ScoreManager;

	UPROPERTY()
	TArray<URaceManager*> RaceManagers;

	UPROPERTY()
	TMap<int, FRaceData> Races;
	
	TArray<FTeamMatchData> Teams;
	
	int CurrentRace = 1;
};

#pragma once

#include "CoreMinimal.h"
#include "Data/TeamData/TeamRosterData.h"
#include "UI/League/Program/Race.h"
#include "MatchManager.generated.h"

class UTeamManager;
class UScoreManager;
class ASMS_GameMode;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMatchFinished, int, int);
DECLARE_MULTICAST_DELEGATE(FOnRaceStared);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnRacerManagersCreated, TArray<UTeamManager*>);
UCLASS()
class SMS_API UMatchManager : public UObject
{
	GENERATED_BODY()

public:

	void AddNewRace(URaceManager* NewRace);
	
	void RequestToAssignRacersToRace(const FRacerMatchData& Data, URacerManager* RacerManager);
	
	void InitializeManager(ASMS_GameMode* CurrentGameMode);
	
	void SetTeamsID(int NewHomeTeamID, int NewVisitorTeamID);

	int GetCurrentRaceNumber()const;

	int GetHomeTeamID() const;

	int GetVisitorTeamID() const;

	int GetAmountOfRaces() const;

	void CreateRacerManagers(TArray<UTeamManager*> TeamManagersRef);
	
	FTeamRosterData* GetHomeTeamData() const;

	FTeamRosterData* GetVisitorTeamData() const;

	FOnMatchFinished OnMatchFinishedDelegate;

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
	int HomeTeamID;

	UPROPERTY()
	int VisitorTeamID;

	UPROPERTY()
	TArray<URaceManager*> RaceManagers;
	
	int CurrentRace = 0;
};
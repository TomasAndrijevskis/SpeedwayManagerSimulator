
#pragma once

#include "CoreMinimal.h"
#include "Data/TeamData/TeamRosterData.h"
#include "UI/League/Program/Race.h"
#include "MatchManager.generated.h"

class UTeamRoster;
class ASMS_GameMode;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMatchFinished, int, int);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnOverallScoreUpdated, int, int);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnNominatedRacesStared, const bool);
DECLARE_MULTICAST_DELEGATE(FOnRaceStared);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPopulateRacersRequest, TArray<UTeamRoster*>);
UCLASS()
class SMS_API UMatchManager : public UObject
{
	GENERATED_BODY()

public:

	void AddNewRace(URace* NewRace);

	void RequestToAssignRacersToRace(const FRacerData& Data, int ID);
	
	void Init(ASMS_GameMode* CurrentGameMode);
	
	void SetTeamsID(int NewHomeTeamID, int NewVisitorTeamID);
	
	int GetHomeTeamScore() const;
	
	int GetVisitorTeamScore() const;

	int GetCurrentRaceNumber()const;

	int GetHomeTeamID() const;

	int GetVisitorTeamID() const;

	int GetAmountOfRaces() const;
	
	FTeamRosterData* GetHomeTeamData() const;

	FTeamRosterData* GetVisitorTeamData() const;

	FOnMatchFinished OnMatchFinishedDelegate;

	FOnOverallScoreUpdated OnOverallScoreUpdatedDelegate;

	FOnNominatedRacesStared OnNominatedRacesStaredDelegate;

	FOnRaceStared OnRaceStaredDelegate;

	FOnPopulateRacersRequest OnPopulateRacersRequestDelegate;
	
private:

	void BindRaceDelegates();

	void BindDelegates();
	
	void HandleRaceFinished();
	
	void SimulateRace();

	void UpdateOverallScore(int AddHomePts, int AddVisitorPts);

	void PopulateRacers(TArray<UTeamRoster*> TeamRosters);
	
	UPROPERTY()
	ASMS_GameMode* GameMode;
	
	UPROPERTY()
	int HomeTeamID;

	UPROPERTY()
	int VisitorTeamID;

	UPROPERTY()
	TArray<URace*> Races;
	
	int HomeOverallScore = 0;

	int VisitorOverallScore = 0;

	int CurrentRace = 0;
};
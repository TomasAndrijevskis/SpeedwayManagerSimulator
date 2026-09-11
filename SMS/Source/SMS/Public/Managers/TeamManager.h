
#pragma once

#include "CoreMinimal.h"
#include "RacerMatchManager.h"
#include "Data/TeamData/TeamMatchData.h"
#include "Data/TeamData/TeamStatistics.h"
#include "TeamManager.generated.h"


class URulesSubsystem;
class ULeague_RacerStatsLine;
class URacerMatchManager;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnTeamScoreUpdated, int32);
UCLASS()
class SMS_API UTeamManager : public UObject
{
	GENERATED_BODY()

public:

	void InitializeManager();
	
	void AddRacersToLineup(const FString& RacerName, int32 RacerStatLineID);

	void ForEachRacerInLineup(TFunction<void(int32)> Callback);
	
	void ForEachRacerInLineup(TFunction<void(const TObjectPtr<URacerMatchManager>&)> Callback);
	
	void GetAvailableReplacementRacers(const URacerMatchManager* OriginalRacerManager, TFunction<void(const TObjectPtr<URacerMatchManager>&)> Callback);
	
	void GetAvailableRacers(TFunction<void(URacerMatchManager*)> Callback);
	
	void ForEachRacerInRoster(TFunction<void(URacerMatchManager*)> Callback);
	
	void SetTeamData(const FTeamMatchData& NewTeamData);

	FString GetTeamName() const;
	
	ETeams GetTeam() const;
	
	int32 GetTeamScore() const;
	
	void UpdateScore(int32 PointsToAdd, int32 RaceID);
	
	int32 GetRaceScore(int32 RaceID) const;
	
	void MakeRandomTeamRoster();//Testing

	void AddRacerStatsLine(ULeague_RacerStatsLine* RacerStatsLine);

	void FillTeamRosterOptions();

	void LockChosenRacers() const;
	
	bool IsRosterValid() const;
	
	TArray<ULeague_RacerStatsLine*>& GetRacerStatsLines();

	bool IsVisitorTeam() const;

	TArray<URacerMatchManager*>& GetRacerManagers();

	TMap<int32, TObjectPtr<URacerMatchManager>>& GetRacers();
	
	void UpdateStatsLineOptions(const ULeague_RacerStatsLine* RacerStatsLineRef, const FString& SelectedOption, const TObjectPtr<URacerMatchManager>& PreviousOptionData);

	void CollectTeamStatistics(const EMatchResults Result, const TMap<ETeams, int32>& OpponentResult);

	FOnTeamScoreUpdated OnTeamScoreUpdatedDelegate;
	
private:

	UPROPERTY()
	FTeamMatchData TeamData;

	//Lineup for current match
	UPROPERTY()
	TMap<int32, TObjectPtr<URacerMatchManager>> Racers;

	UPROPERTY()
	TArray<ULeague_RacerStatsLine*> RacerStatsLines;
	
	UPROPERTY()
	TObjectPtr<URulesSubsystem> RulesSubsystem;
};
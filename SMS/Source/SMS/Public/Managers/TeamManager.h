
#pragma once

#include "CoreMinimal.h"
#include "RacerMatchManager.h"
#include "Data/TeamData/TeamMatchData.h"
#include "Data/TeamData/TeamStatistics.h"
#include "TeamManager.generated.h"


class ULeague_Rules;
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

	void MakeRandomTeamRoster();//Testing

	void FillTeamRosterOptions();

	void LockChosenRacers() const;
	
	bool IsRosterValid() const;

	void UpdateStatsLineOptions(const ULeague_RacerStatsLine* RacerStatsLineRef, const FString& SelectedOption, const TObjectPtr<URacerMatchManager>& PreviousOptionData);

	void CollectTeamStatistics(const EMatchResults Result, const TMap<ETeams, int32>& OpponentResult);
	
	void SetTeamData(const FTeamMatchData& NewTeamData) {TeamData = NewTeamData;}

	FString GetTeamName() const {return TeamData.GetTeamName();}
	
	ETeams GetTeam() const {return TeamData.Team;}
	
	int32 GetTeamScore() const {return TeamData.TeamScore;}
	
	void UpdateScore(int32 PointsToAdd, int32 RaceID);
	
	int32 GetRaceScore(int32 RaceID) const {return TeamData.EachRaceScore[RaceID];}
	
	void AddRacerStatsLine(ULeague_RacerStatsLine* RacerStatsLine) {RacerStatsLines.Add(RacerStatsLine);}
	
	TArray<ULeague_RacerStatsLine*>& GetRacerStatsLines() {return RacerStatsLines;}

	bool IsVisitorTeam() const {return TeamData.IsVisitorTeam;}

	TArray<URacerMatchManager*>& GetRacerManagers()  {return TeamData.Racers;}

	TMap<int32, TObjectPtr<URacerMatchManager>>& GetRacers() {return Racers;}
	
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
	TObjectPtr<ULeague_Rules> LeagueRules;
};
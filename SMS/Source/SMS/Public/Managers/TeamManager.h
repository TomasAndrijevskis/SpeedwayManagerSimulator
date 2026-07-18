
#pragma once

#include "CoreMinimal.h"
#include "RacerManager.h"
#include "Data/RacersData/RacerMatchData.h"
#include "Data/TeamData/TeamMatchData.h"
#include "TeamManager.generated.h"


class URacerStatsLine;
class URacerManager;

UCLASS()
class SMS_API UTeamManager : public UObject
{
	GENERATED_BODY()

public:

	void AddRacersToLineup(const FString& RacerName, int RacerStatLineID);

	void ForEachRacerInLineup(TFunction<void(int)> Callback);
	
	void ForEachRacerInLineup(TFunction<void(const FRacerMatchData&)> Callback);

	void ForEachRacerInLineup(TFunction<void(URacerManager*)> Callback);

	void GetAvailableReplacementRacers(bool IsTeamLosing, bool IsNominatedRace, const URacerManager* RacerManagerRef, TFunction<void(URacerManager*)> Callback);

	void GetAvailableRacers(TFunction<void(URacerManager*)> Callback);
	
	void ForEachRacerInRoster(TFunction<void(const FRacerData&)> Callback);
	
	void SetTeamData(FTeamMatchData* NewTeamData);

	const FString& GetTeamName() const;

	int GetTeamID() const;
	
	void CreateRacerManagers();

	void RandomizeTeamRoster();//Testing

	void AddRacerStatsLine(URacerStatsLine* RacerStatsLine);

	void FillTeamRosterOptions();

	void LockChosenRacers() const;
	
	bool CheckChosenRacers() const;
	
	TArray<URacerStatsLine*>& GetRacerStatsLines();

	bool IsVisitorTeam() const;

	TMap<int, URacerManager*> GetRacerManagers();

	
private:
	
	FTeamMatchData* TeamData;

	//Lineup for current match
	UPROPERTY()
	TMap<int, FRacerMatchData> Racers;

	UPROPERTY()
	TArray<URacerStatsLine*> RacerStatsLines;

	UPROPERTY()
	TMap<int, URacerManager*> RacerManagers;

	TArray<int> ChosenOptions;
};

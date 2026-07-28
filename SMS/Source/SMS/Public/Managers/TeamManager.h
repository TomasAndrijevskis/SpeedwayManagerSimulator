
#pragma once

#include "CoreMinimal.h"
#include "RacerManager.h"
#include "Data/RacersData/RacerMatchData.h"
#include "Data/TeamData/TeamMatchData.h"
#include "TeamManager.generated.h"


class URuleBook;
class URacerStatsLine;
class URacerManager;

UCLASS()
class SMS_API UTeamManager : public UObject
{
	GENERATED_BODY()

public:

	void AddRacersToLineup(const FString& RacerName, int32 RacerStatLineID);

	void ForEachRacerInLineup(TFunction<void(int32)> Callback);
	
	void ForEachRacerInLineup(TFunction<void(const FRacerMatchData&)> Callback);

	void ForEachRacerInLineup(TFunction<void(URacerManager*)> Callback);

	void GetAvailableReplacementRacers(const URacerManager* OriginalRacerManager, TFunction<void(URacerManager*)> Callback);
	
	void GetAvailableRacers(TFunction<void(URacerManager*)> Callback);
	
	void ForEachRacerInRoster(TFunction<void(const FRacerData&)> Callback);
	
	void SetTeamData(FTeamMatchData* NewTeamData);

	void SetRuleBook(URuleBook* NewRuleBook);
	
	const FString& GetTeamName() const;

	int32 GetTeamID() const;
	
	void CreateRacerManagers();

	void MakeRandomTeamRoster();//Testing

	void AddRacerStatsLine(URacerStatsLine* RacerStatsLine);

	void FillTeamRosterOptions();

	void LockChosenRacers() const;
	
	bool IsRosterValid() const;
	
	TArray<URacerStatsLine*>& GetRacerStatsLines();

	bool IsVisitorTeam() const;

	TMap<int32, URacerManager*> GetRacerManagers();

	void UpdateStatsLineOptions(const URacerStatsLine* RacerStatsLineRef, const FString& SelectedOption, FRacerData& PreviousOptionData);
	
private:
	
	FTeamMatchData* TeamData;

	//Lineup for current match
	UPROPERTY()
	TMap<int32, FRacerMatchData> Racers;

	UPROPERTY()
	TArray<URacerStatsLine*> RacerStatsLines;

	UPROPERTY()
	TMap<int32, URacerManager*> RacerManagers;

	UPROPERTY()
	TObjectPtr<URuleBook> RuleBook;
};

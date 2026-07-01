
#pragma once

#include "CoreMinimal.h"
#include "RacerManager.h"
#include "Data/RacersData/RacerMatchData.h"
#include "Data/TeamData/TeamRosterData.h"
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

	void ForEachRacerInLineup(TFunction<void(const FRacerMatchData&, URacerManager*)> Callback);
	
	void ForEachRacerInRoster(TFunction<void(const FRacerData&)> Callback);
	
	void SetTeamData(int ID, bool IsVisitor);

	const FString& GetTeamName() const;

	void CreateRacerManagers();

	void RandomizeTeamRoster();//Testing

	void AddRacerStatsLine(URacerStatsLine* RacerStatsLine);

	void FillTeamRosterOptions();
	
	TArray<URacerStatsLine*>& GetRacerStatsLines();

	bool IsVisitor() const;

	TMap<int, URacerManager*> GetRacerManagers();
	
private:
	
	FTeamRosterData* TeamRosterData;

	//Lineup for current match
	UPROPERTY()
	TMap<int, FRacerMatchData> Racers;

	UPROPERTY()
	TArray<URacerStatsLine*> RacerStatsLines;

	UPROPERTY()
	TMap<int, URacerManager*> RacerManagers;
	
	bool IsVisitorTeam;
};

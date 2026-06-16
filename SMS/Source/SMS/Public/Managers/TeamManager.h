
#pragma once

#include "CoreMinimal.h"
#include "Data/TeamData/TeamRosterData.h"
#include "TeamManager.generated.h"


UCLASS()
class SMS_API UTeamManager : public UObject
{
	GENERATED_BODY()

public:

	void AddRacersToLineup(const FString& RacerName, int RacerStatLineID);
	
	void ForEachRacerInLineup(TFunction<void(int, const FRacerData&)> Callback);

	void ForEachRacerInRoster(TFunction<void(const FRacerData&)> Callback);
	
	void SetTeamData(int ID);

	const FString& GetTeamName() const;
	
private:
	
	FTeamRosterData* TeamRosterData;

	//Lineup for current match
	TMap<int, FRacerData> Racers;
};

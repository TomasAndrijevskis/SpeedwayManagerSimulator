
#pragma once

#include "CoreMinimal.h"
#include "Data/TeamData/TeamRosterData.h"
#include "TeamManager.generated.h"


UCLASS()
class SMS_API UTeamManager : public UObject
{
	GENERATED_BODY()

public:
	
	void ForEachRacer(TFunction<void(const FString&, int)> Callback);

	void ForEachRacer(TFunction<void(const FString&)> Callback);
	
	void SetTeamData(int ID);

	const FString& GetTeamName() const;
	
private:

	void AddRacersToLineup(const FString& RacerName, int RacerStatLineID);
	
	FTeamRosterData* TeamRosterData;

	//Lineup for current match
	TMap<int, FRacerData> Racers;
};

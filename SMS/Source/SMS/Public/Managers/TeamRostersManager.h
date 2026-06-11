
#pragma once

#include "CoreMinimal.h"
#include "Data/TeamData/TeamRosterData.h"
#include "TeamRostersManager.generated.h"


UCLASS()
class SMS_API UTeamRostersManager : public UObject
{
	GENERATED_BODY()

public:

	void AddRacer(FString Name, int RaceStatsLineID);

	void ForEachRacer(TFunction<void(const FString&, int)> Callback);

	void SetTeamData(const FTeamRosterData& Data);
	
private:
	
	TMap<int, FRacerData*> Racers;

	UPROPERTY()
	FTeamRosterData TeamRosterData;
};

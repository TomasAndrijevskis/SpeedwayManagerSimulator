
#pragma once

#include "CoreMinimal.h"
#include "Data/RacersData/RacerData.h"
#include "Data/TeamData/ETeams.h"
#include "GameFramework/GameMode.h"
#include "SMS_GameMode.generated.h"


class URacersDataAsset;
class UTeamsDataAsset;

UCLASS()
class SMS_API ASMS_GameMode : public AGameMode
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	void InitializeRacers();

	void PrintTeams();
	
	TMap<FString, FRacerData> Racers;

	TMap<ETeams, TArray<FString>> Teams;

private:

	UPROPERTY(EditDefaultsOnly)
	UTeamsDataAsset* TeamsDataAsset;

	UPROPERTY(EditDefaultsOnly)
	URacersDataAsset* RacersDataAsset;
};

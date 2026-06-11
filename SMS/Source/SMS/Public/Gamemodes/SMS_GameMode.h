
#pragma once

#include "CoreMinimal.h"
#include "Data/RacersData/RacerData.h"
#include "Data/TeamData/ETeams.h"
#include "Data/TeamData/TeamRosterData.h"
#include "GameFramework/GameMode.h"
#include "SMS_GameMode.generated.h"


class UTeamRostersManager;
class UMatchManager;
class URacersDataAsset;
class UTeamsDataAsset;

UCLASS()
class SMS_API ASMS_GameMode : public AGameMode
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	
	FTeamRosterData* GetTeamData(ETeams Team);

	FTeamRosterData* GetTeamData(int TeamID);

	const FText& GetTeamName(int TeamID);

	const FText& GetTeamName(ETeams Team);
	
	int GetTeamsAmount() const;

	UPROPERTY()
	UMatchManager* MatchManager;
	
private:

	void InitializeRacers();

	void PrintTeams();

	void InitializeManagers();
	
	UPROPERTY(EditDefaultsOnly)
	URacersDataAsset* RacersDataAsset;

	TMap<ETeams, FTeamRosterData> Teams;
};
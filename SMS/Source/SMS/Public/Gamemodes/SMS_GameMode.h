
#pragma once

#include "CoreMinimal.h"
#include "Data/TeamData/ETeams.h"
#include "Data/TeamData/TeamRosterData.h"
#include "GameFramework/GameMode.h"
#include "SMS_GameMode.generated.h"


class UScoreManager;
class UTeamManager;
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

	const FText& GetTeamName(int TeamID)const;

	const FText& GetTeamName(ETeams Team)const;
	
	int GetTeamsAmount() const;

	UPROPERTY()
	UMatchManager* MatchManager;

	UPROPERTY()
	UScoreManager* ScoreManager;
	
private:

	void InitializeRacers();

	void PrintTeams();

	void InitializeManagers();
	
	UPROPERTY(EditDefaultsOnly)
	URacersDataAsset* RacersDataAsset;

	TMap<ETeams, FTeamRosterData> Teams;
};

#pragma once

#include "CoreMinimal.h"
#include "Data/TeamData/ETeams.h"
#include "Data/TeamData/TeamMatchData.h"
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

	FTeamMatchData GetTeamData(int TeamID);

	const FText& GetTeamName(int TeamID) const;
	
	int GetTeamsAmount() const;

	UMatchManager* GetMatchManager() const;

	UScoreManager* GetScoreManager() const;
	
private:

	void InitializeRacers();

	void PrintTeams();

	void InitializeManagers();
	
	UPROPERTY(EditDefaultsOnly)
	URacersDataAsset* RacersDataAsset;

	TMap<ETeams, FTeamMatchData> Teams;
	
	UPROPERTY()
	UMatchManager* MatchManager;

	UPROPERTY()
	UScoreManager* ScoreManager;
	
};
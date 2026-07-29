
#pragma once

#include "CoreMinimal.h"
#include "Data/TeamData/ETeams.h"
#include "Data/TeamData/TeamMatchData.h"
#include "GameFramework/GameMode.h"
#include "SMS_GameMode.generated.h"


class URuleBook;
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

	FTeamMatchData GetTeamData(int32 TeamID);

	const FText& GetTeamName(int32 TeamID) const;
	
	int32 GetTeamsAmount() const;

	UMatchManager* GetMatchManager() const;
	
	void CreateRequiredManagers();

	void DestroyUsedManagers();
	
private:

	void InitializeRacers();

	void PrintTeams();

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataTable> RacersDataTable;
	
	UPROPERTY()
	TObjectPtr<UMatchManager> CurrentMatchManager;
	
	TMap<ETeams, FTeamMatchData> Teams;
};
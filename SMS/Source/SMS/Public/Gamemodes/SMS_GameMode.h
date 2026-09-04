
#pragma once

#include "CoreMinimal.h"
#include "Data/TeamData/ETeams.h"
#include "Data/TeamData/TeamMatchData.h"
#include "GameFramework/GameMode.h"
#include "SMS_GameMode.generated.h"


class ULocationsDataAsset;
class UScoreManager;
class UTeamManager;
class URacersDataAsset;
class UTeamsDataAsset;

UCLASS()
class SMS_API ASMS_GameMode : public AGameMode
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	FTeamMatchData& GetTeamData(ETeams Team);

	const FString& GetTeamName(ETeams Team) const;
	
	int32 GetTeamsAmount() const;

	void InitializeTeamsStatistics();

	TArray<FRacerData> GetTopRacers() const;//temp
	
private:

	void InitializeRacers();

	void SetTrackData();
	
	void PrintTeams();

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataTable> RacersDataTable;

	UPROPERTY(EditDefaultsOnly)
	ULocationsDataAsset* LocationsDataAsset;
	
	TMap<ETeams, FTeamMatchData> Teams;
};
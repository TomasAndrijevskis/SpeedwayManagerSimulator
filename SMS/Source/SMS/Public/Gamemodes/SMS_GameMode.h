
#pragma once

#include "CoreMinimal.h"
#include "Data/TeamData/ETeams.h"
#include "Data/TeamData/TeamData.h"
#include "GameFramework/GameMode.h"
#include "SMS_GameMode.generated.h"


class URacerCareerManager;
class ULocationsDataAsset;
class UTeamManager;
class URacersDataAsset;
class UTeamsDataAsset;

UCLASS()
class SMS_API ASMS_GameMode : public AGameMode
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	FTeamData& GetTeamData(ETeams Team);

	FString GetTeamName(ETeams Team) const;
	
	int32 GetTeamsAmount() const;

	void InitializeTeamsStatistics();

	//TArray<TObjectPtr<URacerCareerManager>> GetTopRacers() const;//temp
	
private:

	void InitializeTeams();

	URacerCareerManager* InitializeRacer(const FRacerData& RacerData);
	
	void SetTrackData();
	
	void PrintTeams();

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataTable> RacersDataTable;

	UPROPERTY(EditDefaultsOnly)
	ULocationsDataAsset* LocationsDataAsset;
	
	TMap<ETeams, FTeamData> Teams;
};
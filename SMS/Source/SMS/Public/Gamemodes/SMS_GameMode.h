
#pragma once

#include "CoreMinimal.h"
#include "Data/Locations/ECities.h"
#include "Data/RacersData/RacerData.h"
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

	void InitializeTeamsStatistics();

	void SetTopRacers();

	FTrackData GetTrackData(ECities CityToFind) const;
	
	TArray<URacerCareerManager*>& GetTopRacers() {return TopRacers;}//temp
	
	FTeamData& GetTeamData(ETeams Team) {return Teams.FindChecked(Team);}

	FString GetTeamName(ETeams Team) const {return Teams.FindChecked(Team).GetTeamName();}
	
	int32 GetTeamsAmount() const {return Teams.Num();}
	
private:

	void InitializeTeams();

	URacerCareerManager* InitializeRacer(const FRacerData& RacerData);
	
	void SetTrackData();
	
	void PrintTeams();

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataTable> RacersDataTable;

	UPROPERTY(EditDefaultsOnly)
	ULocationsDataAsset* LocationsDataAsset;

	UPROPERTY()
	TMap<ETeams, FTeamData> Teams;

	UPROPERTY()
	TArray<URacerCareerManager*> TopRacers;//temp

};
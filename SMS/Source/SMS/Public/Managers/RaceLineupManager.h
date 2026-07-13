
#pragma once

#include "CoreMinimal.h"
#include "Data/RacersData/RacerMatchData.h"
#include "RaceLineupManager.generated.h"

class UTeamManager;
class UScoreManager;
class URaceLineBase;
class URacerManager;

//DECLARE_MULTICAST_DELEGATE_OneParam(FOnHandleRaceLineRequest, bool);
UCLASS()
class SMS_API URaceLineupManager : public UObject
{
	GENERATED_BODY()

public:

	void InitializeManager();
	
	void SetRaceLines(const TArray<URaceLineBase*>& NewRaceLines);
	
	void BindRaceLineDelegates();

	void OnRacerReplaced(const URaceLineBase* RaceLineRef, const FString& RacerName);

	void AssignRacerToRace(const FRacerMatchData& RacerData, URacerManager* RacerManagerRef);

	bool IsTeamLosing(const URaceLineBase* RaceLineRef) const;
	
	//FOnHandleRaceLineRequest OnHandleRaceLineRequestDelegate;
	
private:

	UPROPERTY()
	TArray<URaceLineBase*> RaceLines;

	UPROPERTY()
	UScoreManager* ScoreManager;

	UPROPERTY()
	UTeamManager* TeamManager;
};

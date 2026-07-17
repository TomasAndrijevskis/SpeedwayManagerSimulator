
#pragma once

#include "CoreMinimal.h"
#include "Data/RacersData/RacerMatchData.h"
#include "RaceLineupManager.generated.h"

class UTeamManager;
class UScoreManager;
class URaceLineBase;
class URacerManager;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnHandleRaceLinesRequest, bool);
UCLASS()
class SMS_API URaceLineupManager : public UObject
{
	GENERATED_BODY()

public:

	void InitializeManager();
	
	void HandleRaceLines(bool IsNominatedRace);
	
	void FillOptions(bool IsTeamLosing, bool IsNominatedRace, UTeamManager* TeamManagerRef, const URaceLineBase* RaceLineRef);

	void AddRaceLine(URaceLineBase* NewRaceLine);

	void OnRacerReplaced(URaceLineBase* RaceLineRef, const FString& RacerName);

	void AssignRacerToRace(URacerManager* RacerManagerRef);

	bool IsTeamLosing(URaceLineBase* RaceLineRef) const;

	void OnRacerChosen(URaceLineBase* RaceLineRef, const FString& RacerName);

	void FindSelectedRacer(const FString& SelectedItem, const TFunction<void(URacerManager*)>& Callback);

	virtual void AddOption(URacerManager* NewRacerManager);
	
	void HandleAddedOptions();
	
	void OnRaceInitialized();
	
	FOnHandleRaceLinesRequest OnHandleRaceLinesRequestDelegate;
	
private:

	void BindDelegates();

	void BindRaceLineDelegates();
	
	UPROPERTY()
	TArray<URaceLineBase*> RaceLines;

	UPROPERTY()
	UScoreManager* ScoreManager;

	UPROPERTY()
	UTeamManager* TeamManager;
	
	UPROPERTY()
	TArray<URacerManager*> RacerOptions;
	
	UPROPERTY()
	TArray<URacerManager*> DeniedOptions;
};

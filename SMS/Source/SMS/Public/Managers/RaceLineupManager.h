
#pragma once

#include "CoreMinimal.h"
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

	void AddRaceLine(URaceLineBase* NewRaceLine);

	void AssignRacerToRace(URacerManager* RacerManagerRef);

	bool IsTeamLosing(URaceLineBase* RaceLineRef) const;
	
	void OnRaceInitialized();
	
	FOnHandleRaceLinesRequest OnHandleRaceLinesRequestDelegate;
	
private:

	void BindDelegates();

	void BindRaceLineDelegates();

	void OnRacerChosen(URaceLineBase* RaceLineRef, const FString& RacerName);

	void OnRacerReplaced(URaceLineBase* RaceLineRef, const FString& RacerName);
	
	void FindSelectedRacer(const FString& SelectedItem, TArray<URacerManager*>& OptionsArray, const TFunction<void(URacerManager*)>& Callback);
	
	void HandleAddedOptions(bool IsNominatedRace);

	void AddReplacementOption(URacerManager* NewRacerManager);

	void AddMainOption(URacerManager* NewRacerManager);
	
	void HandleRaceLines(bool IsNominatedRace);

	void HandleOptions(bool IsNominatedRace);
	
	void FillOptions(bool IsTeamLosing, bool IsNominatedRace, UTeamManager* TeamManagerRef, const URaceLineBase* RaceLineRef);

	static void FillOptionsInWidget(TArray<URacerManager*>& OptionsArray, URaceLineBase& RaceLineRef, TFunction<void(URaceLineBase&, const FString&)> AddOption);
	
	UPROPERTY()
	TArray<URaceLineBase*> RaceLines;

	UPROPERTY()
	UScoreManager* ScoreManager;

	UPROPERTY()
	UTeamManager* TeamManager;
	
	UPROPERTY()
	TArray<URacerManager*> RacerReplacementOptions;

	UPROPERTY()
	TArray<URacerManager*> RacerMainOptions;
	
	UPROPERTY()
	TArray<URacerManager*> DeniedOptions;
};

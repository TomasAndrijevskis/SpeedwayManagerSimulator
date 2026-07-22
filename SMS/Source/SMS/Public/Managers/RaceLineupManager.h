
#pragma once

#include "CoreMinimal.h"
#include "RacerManager.h"
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

	static void FindSelectedRacerByName(const FString& SelectedItem, TArray<URacerManager*>& OptionsArray, const TFunction<void(URacerManager*)>& Callback);
	
	void UpdateSelectionWidgets(bool IsNominatedRace);

	void RegisterAvailableReplacementRacer(URacerManager* NewRacerManager);

	void RegisterAvailableMainRacer(URacerManager* NewRacerManager);
	
	void InitializeRaceLineOptions(bool IsNominatedRace);

	void BuildAvailableRacersLists(bool IsNominatedRace);
	
	void FillAvailableRacers(bool IsTeamLosing, bool IsNominatedRace, UTeamManager* TeamManagerRef, const URaceLineBase* RaceLineRef);

	static void FillOptionsInComboBox(TArray<URacerManager*>& OptionsArray, URaceLineBase& RaceLineRef, TFunction<void(URaceLineBase&, const FString&)> AddOption);

	void RestoreRacerAvailability(URaceLineBase* RaceLineRef, URacerManager* RacerManagerRef);
	
	UPROPERTY()
	TArray<URaceLineBase*> RaceLines;

	UPROPERTY()
	UScoreManager* ScoreManager;

	UPROPERTY()
	UTeamManager* TeamManager;
	
	UPROPERTY()
	TArray<URacerManager*> AvailableReplacementRacers;

	UPROPERTY()
	TArray<URacerManager*> AvailableMainRacers;
	
	UPROPERTY()
	TArray<URacerManager*> UnavailableOptions;
};

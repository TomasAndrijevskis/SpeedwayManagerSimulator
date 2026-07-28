
#pragma once

#include "CoreMinimal.h"
#include "RacerManager.h"
#include "RaceLineupManager.generated.h"

class URuleBook;
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

	void AssignRacerToRace(URacerManager* RacerManager);
	
	void OnRaceInitialized();
	
	FOnHandleRaceLinesRequest OnHandleRaceLinesRequestDelegate;
	
private:

	void BindDelegates();

	void BindRaceLineDelegates();

	void OnRacerChosen(URaceLineBase* RaceLineRef, const FString& RacerName);

	void OnRacerReplaced(URaceLineBase* RaceLineRef, const FString& RacerName);

	static void FindSelectedRacerByName(const FString& SelectedItem, TArray<TObjectPtr<URacerManager>>& OptionsArray, const TFunction<void(URacerManager*)>& Callback);
	
	void UpdateReplacementSelectionWidgets();

	void UpdateMainSelectionWidgets();
	
	void InitializeRaceLineOptions(bool IsNominatedRace);

	void BuildAvailableRacersLists(bool IsNominatedRace);
	
	void FillPossibleReplacementRacers(const URaceLineBase* RaceLineRef);

	void FillPossibleMainRacers(UTeamManager* TeamManagerRef);
	
	void FillOptionsInComboBox(TArray<TObjectPtr<URacerManager>>& RacerArray, URaceLineBase& RaceLineRef, TFunction<void(URaceLineBase&, const FString&)> AddOption);

	void RestoreRacerAvailability(URaceLineBase* RaceLineRef, URacerManager* RacerManager);
	
	UPROPERTY()
	TArray<TObjectPtr<URaceLineBase>> RaceLines;
	
	UPROPERTY()
	TObjectPtr<UTeamManager> TeamManager;
	
	UPROPERTY()
	TArray<TObjectPtr<URacerManager>> UnavailableRacers;
	
	TMap<TObjectPtr<URacerManager>, TArray<TObjectPtr<URacerManager>>> PossibleRacers;
};

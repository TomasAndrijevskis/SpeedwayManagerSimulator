
#pragma once

#include "CoreMinimal.h"
#include "RacerManager.h"
#include "RaceLineupManager.generated.h"

class ULeague_RaceLine_Base;
class UTeamManager;
class UScoreManager;
class URacerManager;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnHandleRaceLinesRequest, bool);
UCLASS()
class SMS_API URaceLineupManager : public UObject
{
	GENERATED_BODY()

public:

	void InitializeManager();

	void AddRaceLine(ULeague_RaceLine_Base* NewRaceLine);

	void AssignRacerToRace(URacerManager* RacerManager);
	
	void OnRaceInitialized();
	
	FOnHandleRaceLinesRequest OnHandleRaceLinesRequestDelegate;
	
private:

	void BindDelegates();

	void BindRaceLineDelegates();

	void OnRacerChosen(ULeague_RaceLine_Base* RaceLineRef, const FString& RacerName);

	void OnRacerReplaced(ULeague_RaceLine_Base* RaceLineRef, const FString& RacerName, URacerManager* OriginalRacerManager);

	static void FindSelectedRacerByName(const FString& SelectedItem, TArray<TObjectPtr<URacerManager>>& OptionsArray, const TFunction<void(URacerManager*)>& Callback);
	
	void UpdateReplacementSelectionWidgets();

	void UpdateMainSelectionWidgets();
	
	void InitializeRaceLineOptions(bool IsNominatedRace);

	void BuildAvailableRacersLists(bool IsNominatedRace);
	
	void FillPossibleReplacementRacers(const ULeague_RaceLine_Base* RaceLineRef);

	void FillPossibleMainRacers(UTeamManager* TeamManagerRef);
	
	void FillOptionsInComboBox(TArray<TObjectPtr<URacerManager>>& RacerArray, ULeague_RaceLine_Base& RaceLineRef, TFunction<void(ULeague_RaceLine_Base&, const FString&)> AddOption);

	void RestoreRacerAvailability(ULeague_RaceLine_Base* RaceLineRef, URacerManager* RacerManager, bool bIsReplacement);
	
	UPROPERTY()
	TArray<TObjectPtr<ULeague_RaceLine_Base>> RaceLines;
	
	UPROPERTY()
	TObjectPtr<UTeamManager> TeamManager;
	
	UPROPERTY()
	TArray<TObjectPtr<URacerManager>> UnavailableRacers;
	
	TMap<TObjectPtr<URacerManager>, TArray<TObjectPtr<URacerManager>>> PossibleRacers;
};

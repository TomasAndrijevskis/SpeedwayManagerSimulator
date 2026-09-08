
#pragma once

#include "CoreMinimal.h"
#include "RacerMatchManager.h"
#include "RaceLineupManager.generated.h"

class ULeague_RaceLine_Base;
class UTeamManager;
class URacerMatchManager;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnHandleRaceLinesRequest, bool);
UCLASS()
class SMS_API URaceLineupManager : public UObject
{
	GENERATED_BODY()

public:

	void InitializeManager();

	void AddRaceLine(ULeague_RaceLine_Base* NewRaceLine);

	void AssignRacerToRace(URacerMatchManager* RacerManager);
	
	void OnRaceInitialized();
	
	FOnHandleRaceLinesRequest OnHandleRaceLinesRequestDelegate;
	
private:

	void BindDelegates();

	void BindRaceLineDelegates();

	void OnRacerChosen(ULeague_RaceLine_Base* RaceLineRef, const FString& RacerName);

	void OnRacerReplaced(ULeague_RaceLine_Base* RaceLineRef, const FString& RacerName, URacerMatchManager* OriginalRacerManager);

	static void FindSelectedRacerByName(const FString& SelectedItem, TArray<TObjectPtr<URacerMatchManager>>& OptionsArray, const TFunction<void(URacerMatchManager*)>& Callback);
	
	void UpdateReplacementSelectionWidgets();

	void UpdateMainSelectionWidgets();
	
	void InitializeRaceLineOptions(bool IsNominatedRace);

	void BuildAvailableRacersLists(bool IsNominatedRace);
	
	void FillPossibleReplacementRacers(const ULeague_RaceLine_Base* RaceLineRef);

	void FillPossibleMainRacers(const ULeague_RaceLine_Base* RaceLineRef);
	
	void FillOptionsInComboBox(TArray<TObjectPtr<URacerMatchManager>>& RacerArray, ULeague_RaceLine_Base& RaceLineRef, TFunction<void(ULeague_RaceLine_Base&, const FString&)> AddOption);

	void RestoreRacerAvailability(ULeague_RaceLine_Base* RaceLineRef, URacerMatchManager* RacerManager, bool bIsReplacement);
	
	UPROPERTY()
	TArray<TObjectPtr<ULeague_RaceLine_Base>> RaceLines;
	
	UPROPERTY()
	TArray<TObjectPtr<URacerMatchManager>> UnavailableRacers;
	
	TMap<TObjectPtr<URacerMatchManager>, TArray<TObjectPtr<URacerMatchManager>>> PossibleRacers;
};

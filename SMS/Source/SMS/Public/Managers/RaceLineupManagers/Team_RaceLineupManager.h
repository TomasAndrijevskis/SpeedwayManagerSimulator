
#pragma once

#include "CoreMinimal.h"
#include "RaceLineupManager.h"
#include "Team_RaceLineupManager.generated.h"


class ULeague_RaceLine_Base;

UCLASS()
class SMS_API UTeam_RaceLineupManager : public URaceLineupManager
{
	GENERATED_BODY()

public:

	void OnRaceInitialized();

private:

	virtual void BindDelegates() override;

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
	TArray<TObjectPtr<URacerMatchManager>> UnavailableRacers;
	
	TMap<TObjectPtr<URacerMatchManager>, TArray<TObjectPtr<URacerMatchManager>>> PossibleRacers;
};

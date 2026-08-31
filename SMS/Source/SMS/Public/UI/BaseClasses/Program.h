
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/RaceData/RaceResultData.h"
#include "Program.generated.h"


class URace;
class URaceStats;
class UBackgroundBlur;
class UTextBlock;
class UButton;
class UCanvasPanel;
class UMatchManager;

UCLASS()
class SMS_API UProgram : public UUserWidget
{
	GENERATED_BODY()

public:

	void InitializeManagers();

protected:

	UFUNCTION()
	virtual void PopulateRacers() {};

	virtual void BindDelegates(); 
	
	void CreateRaces();
	
	URace* CreateRace(const FAnchors& Anchors, const FVector2d& Position, const FVector2d& Alignment);

	void OnRaceStatsUpdated(const TArray<FRaceResultData>& Data);

	virtual void CollectStatistics() {};
	
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* CanvasPanel_Root;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_SimulateRace;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_SimulateMatch;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_SimulateButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* Button_ConfirmRacers;
	
	UPROPERTY(meta = (BindWidget))
	UBackgroundBlur* BackgroundBlur;

	UPROPERTY(meta = (BindWidget))
	URaceStats* RaceStatsWidget;
	
	UPROPERTY()
	TObjectPtr<UMatchManager> MatchManager;

	UPROPERTY(EditDefaultsOnly)
	int32 AmountOfRaces = 0;

	UPROPERTY(EditDefaultsOnly)
	FVector2D StartPosition = FVector2D(0,-540);

private:

	UFUNCTION()
	void StartRace();

	UFUNCTION()
	void SimulateMatch();

	UFUNCTION()
	void PrepareToEndMatch();

	void ChangeButtonBehaviour();

	UFUNCTION()
	void FinishMatch();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<URace> RaceClass;
};

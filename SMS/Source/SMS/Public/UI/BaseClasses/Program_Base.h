
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/RaceData/RaceResultData.h"
#include "Program_Base.generated.h"


class URacePatternsDataAsset;
class URace_Base;
class ULeague_Race;
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

protected:

	UPROPERTY(meta = (BindWidget))
	UBackgroundBlur* BackgroundBlur;
	
	UFUNCTION()
	virtual void PopulateRacers(){};

	virtual void BindDelegates(); 

	virtual void CollectStatistics(){};

	virtual void DisableButtons(){};
	
	void CreateRaces();
	
	URace_Base* CreateRace(const FAnchors& Anchors, const FVector2d& Position, const FVector2d& Alignment);

	void OnRaceStatsUpdated(const TArray<FRaceResultData>& Data);

	void CreateRaceStatsWidget();

	UPROPERTY(EditDefaultsOnly)
	FVector2D StartPosition = FVector2D(0,-540);

	UPROPERTY(EditDefaultsOnly)
	float Offset = 0.5f;

	UPROPERTY(EditDefaultsOnly)
	int32 AmountOfRows = 0;
	
private:
	
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* CanvasPanel_Root;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_SimulateRace;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_SimulateMatch;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_SimulateButton;

	UPROPERTY(meta = (BindWidget))
	URaceStats* RaceStatsWidget;
	
	UFUNCTION()
	void StartRace();

	UFUNCTION()
	void SimulateMatch();

	UFUNCTION()
	void PrepareToEndMatch();

	void ChangeButtonBehaviour();

	UFUNCTION()
	void FinishMatch();
	
	UPROPERTY(EditDefaultsOnly, meta = (BlueprintBaseOnly))
	TSubclassOf<URace_Base> RaceClass;

	UPROPERTY(EditDefaultsOnly)
	URacePatternsDataAsset* RacePatternDataAsset;
};

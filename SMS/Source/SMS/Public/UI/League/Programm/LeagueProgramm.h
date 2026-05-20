
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LeagueProgramm.generated.h"

class URacerStatsLine;
class UCanvasPanel;
class UBackgroundBlur;
class UVerticalBox;
class UTeamLineup;
class UButton;
class URace;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnScoreUpdated, int, int)
UCLASS()
class SMS_API ULeagueProgramm : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void SetOverallPts(int AddHomePts, int AddVisitorPts);

	FOnScoreUpdated OnScoreUpdatedDelegate;
	
protected:

	virtual void NativeConstruct() override;
	
private:

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* CanvasPanel_Root;
	
	UPROPERTY(meta = (BindWidget))
	UTeamLineup* TeamLineup_HomeTeam;

	UPROPERTY(meta = (BindWidget))
	UTeamLineup* TeamLineup_VisitorTeam;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_SimulateRace;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_ShowTeams;
	
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VB_Teams;

	UPROPERTY(meta = (BindWidget))
	UBackgroundBlur* BackgroundBlur;
	
	UFUNCTION()
	void SimulateRace();

	void FillRacers(FString Name, int Id);

	void BindDelegates();

	UFUNCTION()
	void ShowTeams();

	void CreateRaces();

	URace* CreateRace(const FAnchors& Anchors, const FVector2d& Position, const FVector2d& Alignment);

	void OnRaceFinished(int ID, int NewPoints);

	void AddRacerPoints(int ID, int NewPoints, TArray<URacerStatsLine*>& Racers);
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<URace> RaceClass;

	UPROPERTY(EditDefaultsOnly)
	int AmountOfRaces = 15;
	
	TArray<URace*> Races;

	FVector2d StartPosition = FVector2d(0,-540);

	int CurrentRace = 0;
	
	int HomeOverallPts = 0;

	int VisitorOverallPts = 0;
};
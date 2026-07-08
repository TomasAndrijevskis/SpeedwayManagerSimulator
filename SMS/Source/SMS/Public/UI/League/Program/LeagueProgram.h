
#pragma once

#include "CoreMinimal.h"
#include "Race.h"
#include "Blueprint/UserWidget.h"
#include "Data/TeamData/TeamMatchData.h"
#include "LeagueProgram.generated.h"

class UTeamManager;
class UFillNominatedRaces;
class UMatchManager;
class URacerStatsLine;
class UCanvasPanel;
class UBackgroundBlur;
class UVerticalBox;
class UTeamRoster;
class UButton;


UCLASS()
class SMS_API ULeagueProgram : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void InitializeManagers();

protected:

	virtual void NativeConstruct() override;
	
private:

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* CanvasPanel_Root;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_SimulateRace;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_SimulateButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* Button_ShowTeams;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_RandomizeTeamRosters;
	
	UPROPERTY(meta = (BindWidget))
	UButton* Button_ConfirmTeams;
	
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VB_Teams;

	UPROPERTY(meta = (BindWidget))
	UBackgroundBlur* BackgroundBlur;

	void InitializeTeams();

	UTeamRoster* CreateTeamRoster(FTeamMatchData* TeamData);

	void RegisterTeamRoster(UTeamRoster* TeamRoster);
	
	UFUNCTION()
	void PopulateRacers();
	
	void BindDelegates();

	UFUNCTION()
	void ShowTeams();

	void CreateRaces();
	
	URace* CreateRace(const FAnchors& Anchors, const FVector2d& Position, const FVector2d& Alignment);

	UFUNCTION()
	void StartRace();

	UFUNCTION()
	void RandomizeTeamRosters();//Testing

	UFUNCTION()
	void DisableButtons();

	UFUNCTION()
	void FinishMatch();

	UFUNCTION()
	void ChangeButtonBehaviour();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<URace> RaceClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UTeamRoster> TeamRosterClass;
	
	UPROPERTY(VisibleAnywhere)
	int AmountOfRaces = 15;

	TArray<UTeamManager*> TeamManagers;
	
	FVector2d StartPosition = FVector2d(0,-540);

	UPROPERTY()
	UMatchManager* MatchManager;
};
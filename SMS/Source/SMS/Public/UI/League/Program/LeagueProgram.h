
#pragma once

#include "CoreMinimal.h"
#include "Race.h"
#include "Blueprint/UserWidget.h"
#include "LeagueProgram.generated.h"

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
	UButton* Button_ShowTeams;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_ConfirmTeams;
	
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VB_Teams;

	UPROPERTY(meta = (BindWidget))
	UBackgroundBlur* BackgroundBlur;

	void InitializeTeams();

	UTeamRoster* CreateTeamRoster(int TeamID, bool IsVisitor);

	void RegisterTeamRoster(UTeamRoster* TeamRoster);
	
	UFUNCTION()
	void PopulateRacers();
	
	void BindDelegates();

	UFUNCTION()
	void ShowTeams();

	void CreateRaces();

	UFUNCTION()
	void FillNominatedRaces();
	
	URace* CreateRace(const FAnchors& Anchors, const FVector2d& Position, const FVector2d& Alignment);

	UFUNCTION()
	void StartRace();

	void BindSimulateButtonAction(const bool IsNominatedRace);
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<URace> RaceClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UTeamRoster> TeamRosterClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UFillNominatedRaces> FillNominatedRacesClass;
	
	UPROPERTY(VisibleAnywhere)
	int AmountOfRaces = 15;

	TArray<UTeamRoster*> TeamRosters;
	
	FVector2d StartPosition = FVector2d(0,-540);

	UPROPERTY()
	UMatchManager* MatchManager;
};
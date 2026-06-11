
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/TeamData/TeamRosterData.h"
#include "LeagueProgram.generated.h"

class UMatchManager;
class URacerStatsLine;
class UCanvasPanel;
class UBackgroundBlur;
class UVerticalBox;
class UTeamRoster;
class UButton;
class URace;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnScoreUpdated, int, int)
UCLASS()
class SMS_API ULeagueProgram : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void InitializeMatchManager();
	
	FOnScoreUpdated OnScoreUpdatedDelegate;
	
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

	UTeamRoster* CreateTeamRoster(const FTeamRosterData* TeamData, bool IsVisitor);

	void RegisterTeamRoster(UTeamRoster* TeamRoster);
	
	void AssignRacers(const FString& Name, int Id);
	
	UFUNCTION()
	void PopulateRacers();
	
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
	TSubclassOf<UTeamRoster> TeamRosterClass;
	
	UPROPERTY(EditDefaultsOnly)
	int AmountOfRaces = 15;
	
	TArray<URace*> Races;

	TArray<UTeamRoster*> TeamRosters;
	
	FVector2d StartPosition = FVector2d(0,-540);

	UPROPERTY()
	UMatchManager* MatchManager;
	
	int HomeOverallPts = 0;

	int VisitorOverallPts = 0;
};

#pragma once

#include "CoreMinimal.h"
#include "Data/TeamData/TeamMatchData.h"
#include "UI/BaseClasses/Program.h"
#include "LeagueProgram.generated.h"


class UTeamManager;
class UTeamRoster;
class UVerticalBox;

UCLASS()
class SMS_API ULeagueProgram : public UProgram
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

	virtual void CollectStatistics() override;
	
private:
	
	UPROPERTY(meta = (BindWidget))
	UButton* Button_ShowTeams;
	
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VB_Teams;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_RandomizeTeamRosters;
	
	void InitializeTeams();

	UTeamRoster* CreateTeamRoster(FTeamMatchData* TeamData);

	void RegisterTeamRoster(UTeamRoster* TeamRoster);
	
	virtual void PopulateRacers() override;
	
	virtual void BindDelegates() override;

	UFUNCTION()
	void ShowTeams();
	
	UFUNCTION()
	void RandomizeTeamRosters();

	UFUNCTION()
	void DisableButtons();

	void CreateRaceStatsWidget();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UTeamRoster> TeamRosterClass;

	TArray<TObjectPtr<UTeamManager>> TeamManagers;
};
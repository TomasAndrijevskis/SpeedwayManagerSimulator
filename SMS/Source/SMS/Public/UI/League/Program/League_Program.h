
#pragma once

#include "CoreMinimal.h"
#include "Data/TeamData/TeamMatchData.h"
#include "UI/BaseClasses/Program_Base.h"
#include "League_Program.generated.h"


class UTeamManager;
class UTeamRoster;
class UVerticalBox;

UCLASS()
class SMS_API ULeague_Program : public UProgram
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;
	
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

	virtual void CollectStatistics() override;

	virtual void DisableButtons() override;
	
	UFUNCTION()
	void ShowTeams();
	
	UFUNCTION()
	void RandomizeTeamRosters();
	
	UPROPERTY(EditDefaultsOnly, meta = (BlueprintBaseOnly))
	TSubclassOf<UTeamRoster> TeamRosterClass;

	TArray<TObjectPtr<UTeamManager>> TeamManagers;
};
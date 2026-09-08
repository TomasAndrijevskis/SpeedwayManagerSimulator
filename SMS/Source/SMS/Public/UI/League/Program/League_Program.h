
#pragma once

#include "CoreMinimal.h"
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
	
	UPROPERTY(meta = (BindWidget))
	UButton* Button_ConfirmRacers;
	
	void InitializeTeams();

	void CreateTeamRoster(bool IsVisitor);

	UFUNCTION()
	virtual void PopulateRacers() override;
	
	virtual void BindDelegates() override;

	virtual void DisableButtons() override;
	
	UFUNCTION()
	void ShowTeams();
	
	UFUNCTION()
	void RandomizeTeamRosters();
	
	UPROPERTY(EditDefaultsOnly, meta = (BlueprintBaseOnly))
	TSubclassOf<UTeamRoster> TeamRosterClass;
};

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseClasses/Program_Base.h"
#include "League_Program.generated.h"


class UTeamManager;
class UTeamRoster;

UCLASS()
class SMS_API ULeague_Program : public UProgram
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;
	
private:

	UPROPERTY(meta = (BindWidget))
	UButton* Button_RandomizeRacers;
	
	void InitializeTeams();

	void CreateTeamRoster(bool IsVisitor);
	
	virtual void PopulateRacers() override;
	
	virtual void BindDelegates() override;

	virtual void DisableButtons() override;

	virtual void RandomizeRacers() override;
	
	UPROPERTY(EditDefaultsOnly, meta = (BlueprintBaseOnly))
	TSubclassOf<UTeamRoster> TeamRosterClass;
};
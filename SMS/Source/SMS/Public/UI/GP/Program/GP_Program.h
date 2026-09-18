
#pragma once

#include "CoreMinimal.h"
#include "UI/BaseClasses/Program_Base.h"
#include "GP_Program.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnLineupDisplayed);
class UGP_Lineup;
class ASMS_GameMode;

UCLASS()
class SMS_API UGPProgram : public UProgram
{
	GENERATED_BODY()

public:

	FOnLineupDisplayed OnLineupDisplayedDelegate;
	
protected:

	virtual void NativeConstruct() override;
	
private:
	
	virtual void DisableButtons() override;
	
	virtual void PopulateRacers() override;
	
	virtual void RandomizeRacers() override;
	
	void CreateLineup();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGP_Lineup> LineupClass;
};


#pragma once

#include "CoreMinimal.h"
#include "UI/BaseClasses/Program_Base.h"
#include "GP_Program.generated.h"


UCLASS()
class SMS_API UGPProgram : public UProgram
{
	GENERATED_BODY()

public:

	virtual void InitializeManagers() override;
	
protected:

	virtual void NativeConstruct() override;
	
private:

	UPROPERTY(meta = (BindWidget))
	UButton* Button_RandomizeLineup;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_ShowLineup;

	virtual void DisableButtons() override;
	
	//virtual void PopulateRacers() override;
};

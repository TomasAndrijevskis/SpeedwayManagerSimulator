
#pragma once

#include "CoreMinimal.h"
#include "UI/BaseClasses/Program.h"
#include "GP_Program.generated.h"


UCLASS()
class SMS_API UGPProgram : public UProgram
{
	GENERATED_BODY()

public:

private:

	UPROPERTY(meta = (BindWidget))
	UButton* Button_RandomizeLineup;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_ShowLineup;
};

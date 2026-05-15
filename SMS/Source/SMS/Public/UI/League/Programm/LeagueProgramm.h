
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LeagueProgramm.generated.h"

class UButton;
class URace;
class URacerStatsLine;

UCLASS()
class SMS_API ULeagueProgramm : public UUserWidget
{
	GENERATED_BODY()
public:

protected:

	virtual void NativeConstruct() override;
	
private:

	UPROPERTY(meta = (BindWidget))
	URacerStatsLine* RacerStatsLine_First;
	
	UPROPERTY(meta = (BindWidget))
	URacerStatsLine* RacerStatsLine_Second;

	UPROPERTY(meta = (BindWidget))
	URacerStatsLine* RacerStatsLine_Third;

	UPROPERTY(meta = (BindWidget))
	URacerStatsLine* RacerStatsLine_Fourth;

	UPROPERTY(meta = (BindWidget))
	URace* Race_First;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_SimulateRace;

	UFUNCTION()
	void SimulateRace();
	
};

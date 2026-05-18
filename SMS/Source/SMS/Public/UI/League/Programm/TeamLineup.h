
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TeamLineup.generated.h"


class UNamesBox;
class URacerStatsLine;

UCLASS()
class SMS_API UTeamLineup : public UUserWidget
{
	GENERATED_BODY()

public:

	TArray<URacerStatsLine*>& GetRacers();
	
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
	URacerStatsLine* RacerStatsLine_Fifth;
	
	UPROPERTY(meta = (BindWidget))
	URacerStatsLine* RacerStatsLine_Sixth;

	UPROPERTY(meta = (BindWidget))
	UNamesBox* NamesBox_TeamName;

	UPROPERTY(meta = (BindWidget))
	UNamesBox* NamesBox_TeamStatus;
	
	void SetRacerID();
	
	TArray<URacerStatsLine*> Racers;
	
};

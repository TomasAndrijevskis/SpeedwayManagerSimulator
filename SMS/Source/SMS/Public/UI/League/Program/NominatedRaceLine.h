
#pragma once

#include "CoreMinimal.h"
#include "RaceLineBase.h"
#include "Data/RaceData/RaceLineData.h"
#include "NominatedRaceLine.generated.h"


class UChooseBox;
class UNumbersBox;

UCLASS()
class SMS_API UNominatedRaceLine : public URaceLineBase
{
	GENERATED_BODY()
	
public:
	 
	virtual void SetRaceLineData(const FRaceLineData& NewRaceLineData) override;

	
protected:
	
	virtual void BindDelegates() override;

	virtual void HandleFillingOptions(bool bIsActive, bool bCanReplace) override;
	
private:

	UPROPERTY(meta = (BindWidget))
	UChooseBox* ChooseBox_ChooseMainRacer;
	
	virtual void AddOption(const FRacerMatchData& Data, URacerManager* NewRacerManager) override;
};

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

	virtual void AddMainOption(FString SelectedItem) override;
	virtual void RemoveFromMainSelection(FString SelectedItem) override;

protected:
	
	virtual void BindDelegates() override;

	virtual void OnRacerChosen(FString SelectedItem, ESelectInfo::Type SelectionType) override;
	
private:

	UPROPERTY(meta = (BindWidget))
	UChooseBox* ChooseBox_ChooseMainRacer;
	
};
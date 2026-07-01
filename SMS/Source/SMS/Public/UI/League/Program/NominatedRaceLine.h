
#pragma once

#include "CoreMinimal.h"
#include "RaceLineBase.h"
#include "Data/RaceData/RaceLineData.h"
#include "NominatedRaceLine.generated.h"


class UTeamManager;
class UChooseBox;
class UNumbersBox;

UCLASS()
class SMS_API UNominatedRaceLine : public URaceLineBase
{
	GENERATED_BODY()
	
public:

	void SetRaceLineData(const FRaceLineData& NewRaceLineData, const TArray<UTeamManager*>& TeamManagers);

	void FillOptions();

	void AddOption(const FString& RacerName);

protected:

	//virtual void SetRacerName(const FString& NewRacerName) override;
	
private:

	UPROPERTY(meta = (BindWidget))
	UChooseBox* ChooseBox_ChooseRacer;
	
	UPROPERTY()
	UTeamManager* TeamManager;
};
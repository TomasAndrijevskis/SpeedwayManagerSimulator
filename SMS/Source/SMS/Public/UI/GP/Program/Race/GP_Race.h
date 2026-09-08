
#pragma once

#include "CoreMinimal.h"
#include "UI/BaseClasses/Race_Base.h"
#include "GP_Race.generated.h"


class UGP_RaceLine_Base;
class UVerticalBox;
class UNumbersBox;

UCLASS()
class SMS_API UGPRace : public URace_Base
{
	GENERATED_BODY()

public:

	virtual void InitializeWidget(int32 NewID) override;

private:

	virtual void InitializeRaceData() override;

	virtual void BindDelegates() override;

	virtual void CreateRaceLines() override;

	UGP_RaceLine_Base* CreateRaceLine(int32 RaceLineID);
};

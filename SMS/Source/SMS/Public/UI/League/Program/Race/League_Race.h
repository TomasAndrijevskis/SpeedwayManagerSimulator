
#pragma once

#include "CoreMinimal.h"
#include "UI/BaseClasses/Race_Base.h"
#include "League_Race.generated.h"


class UScoreCounter;
class ULeague_RaceLine_Base;

UCLASS()
class SMS_API ULeague_Race : public URace_Base
{
	GENERATED_BODY()

public:

	virtual void InitializeWidget(int32 NewID) override;

private:

	UPROPERTY(meta = (BindWidget))
	UScoreCounter* ScoreCounter;
	
	virtual void InitializeRaceData() override;
	
	virtual void BindDelegates() override;

	virtual void CreateRaceLines() override;
	
	ULeague_RaceLine_Base* CreateRaceLine(int32 RaceLineID);

	ULeague_RaceLine_Base* CreateNominatedRaceLine(int32 RaceLineID);

	void UpdateScore();
	
	UPROPERTY(EditDefaultsOnly, meta = (BlueprintBaseOnly))
	TSubclassOf<ULeague_RaceLine_Base> NominatedRaceLineClass;
};
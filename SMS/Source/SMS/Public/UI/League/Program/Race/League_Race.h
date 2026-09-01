
#pragma once

#include "CoreMinimal.h"
#include "UI/BaseClasses/Race_Base.h"
#include "League_Race.generated.h"


class ULeague_RaceLine_Base;
class UScoreCounter;

UCLASS()
class SMS_API ULeague_Race : public URace_Base
{
	GENERATED_BODY()

public:

	virtual void InitializeWidget(int32 NewID, UScoreManager* ScoreManagerRef) override;

private:

	UPROPERTY(meta = (BindWidget))
	UScoreCounter* ScoreCounter;
	
	virtual void InitializeRaceData() override;
	
	virtual void BindDelegates() override;

	virtual void CreateRaceLines() override;
	
	ULeague_RaceLine_Base* CreateRaceLine(int32 RaceLineID);

	ULeague_RaceLine_Base* CreateNominatedRaceLine(int32 RaceLineID);

	void UpdateRacePoints();
    
	void UpdateOverallScore();

	UPROPERTY(EditDefaultsOnly, meta = (BlueprintBaseOnly))
	TSubclassOf<ULeague_RaceLine_Base> NominatedRaceLineClass;

	UPROPERTY()
	TObjectPtr<UScoreManager> ScoreManager;
};
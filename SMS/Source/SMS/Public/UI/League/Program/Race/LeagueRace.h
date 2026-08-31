
#pragma once

#include "CoreMinimal.h"
#include "UI/BaseClasses/Race_Base.h"
#include "LeagueRace.generated.h"


class URaceLineBase;
class UScoreCounter;

UCLASS()
class SMS_API ULeagueRace : public URace_Base
{
	GENERATED_BODY()

public:

	virtual void InitializeWidget(int32 NewID, UScoreManager* ScoreManagerRef) override;

	bool IsNominatedRace() const;

private:

	UPROPERTY(meta = (BindWidget))
	UScoreCounter* ScoreCounter;
	
	virtual void InitializeRaceData() override;
	
	virtual void BindDelegates() override;

	virtual void CreateRaceLines() override;
	
	URaceLineBase* CreateRaceLine(int32 RaceLineID);

	URaceLineBase* CreateNominatedRaceLine(int32 RaceLineID);

	void UpdateRacePoints();
    
	void UpdateOverallScore();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<URaceLineBase> RaceLineClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<URaceLineBase> NominatedRaceLineClass;

	UPROPERTY()
	TObjectPtr<UScoreManager> ScoreManager;
};
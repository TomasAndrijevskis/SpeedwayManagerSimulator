
#pragma once

#include "CoreMinimal.h"
#include "RacerManager.h"
#include "RuleBook.generated.h"


class URacerManager;
class URaceLineBase;
class UScoreManager;
class URacerStatsLine;

UCLASS()
class SMS_API URuleBook : public UObject
{
	GENERATED_BODY()

public:

	void InitializeRules(UScoreManager* Manager);
	
	bool IsRacerEligible(const URacerStatsLine* RacerStatsLineRef, int Age) const;
	
	bool CanReplace(const URacerManager* OriginalRacer, const URacerManager* ReplacementRacer) const;
	
	bool IsTeamLosing(const URacerManager* RacerManagerRef) const;

	bool CanParticipateInNominatedRace(const URacerManager* RacerManagerRef) const;

private:

	bool IsJunior(int32 RacerAge) const;

	bool IsOnJuniorPosition(int32 RacerNumber) const;

	bool IsReplacement(int32 RacerNumber) const;
	
	UPROPERTY()
	TObjectPtr<UScoreManager> ScoreManager;
	
	TArray<int32> JuniorPositions = {5, 11};

	TArray<int32> ReplacementPositions = {6, 12};

	int32 JuniorAge = 23;

	int32 MaxAmountOfRaces = 7;

	int32 TeamScoreDifference = 6;
};

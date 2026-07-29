
#pragma once

#include "CoreMinimal.h"
#include "RacerManager.h"
#include "Data/RacersData/EPositionTypes.h"
#include "Data/RacersData/ReplacementRule.h"
#include "RuleBook.generated.h"


class URacerStatsLine;
class UScoreManager;

UCLASS()
class SMS_API URuleBook : public UObject
{
	GENERATED_BODY()

public:

	void InitializeRules(UScoreManager* Manager);
	
	bool IsRacerEligible(const URacerStatsLine* RacerStatsLineRef, int32 Age) const;
	
	bool CanReplace(const URacerManager* OriginalRacer, const URacerManager* ReplacementRacer) const;
	
	bool IsTeamLosing(const URacerManager* RacerManagerRef) const;

	bool CanParticipateInNominatedRace(const URacerManager* RacerManagerRef) const;

private:

	bool IsJunior(int32 RacerAge) const;

	EPositionTypes GetPositionType(int32 RacerNumber) const;
	
	//bool CheckPossibleAmountOfReplacements(int32 AmountOfReplacements) const;
	
	UPROPERTY()
	TObjectPtr<UScoreManager> ScoreManager;
	
	TArray<EPositionTypes> Positions;
	
	TArray<FReplacementRule> ReplacementRules;

	int32 RacersAmount = 12;
	
	int32 JuniorAge = 23;

	int32 MaxAmountOfRaces = 7;

	int32 TeamScoreDifference = 6;
};
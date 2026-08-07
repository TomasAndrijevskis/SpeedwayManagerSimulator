
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Data/RacersData/EPositionTypes.h"
#include "Data/RacersData/ReplacementRule.h"
#include "RulesSubsystem.generated.h"

class URacerManager;
class URacerStatsLine;
class UScoreManager;

UCLASS()
class SMS_API URulesSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	void InitializeRules();
	
	bool IsRacerEligible(int32 RaceLineID, int32 Age) const;
	
	bool CanReplace(const URacerManager* OriginalRacer, const URacerManager* ReplacementRacer, int32 OwnTeamScore, int32 EnemyTeamScore) const;

	bool IsTeamLosing(int32 OwnTeamScore, int32 EnemyTeamScore) const;
	
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

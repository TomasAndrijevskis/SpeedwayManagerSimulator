
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Data/Rules/ReplacementRule.h"
#include "Data/Rules/EPositionTypes.h"
#include "Data/Rules/ERaceResults.h"
#include "RulesSubsystem.generated.h"

class UTeamManager;
class URacerMatchManager;
class ULeague_RacerStatsLine;

UCLASS()
class SMS_API URulesSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	void InitializeRules();
	
	bool IsRacerEligible(int32 RaceLineID, int32 Age) const;
	
	bool CanReplace(const URacerMatchManager* OriginalRacer, const URacerMatchManager* ReplacementRacer, int32 OwnTeamScore, int32 EnemyTeamScore) const;

	bool IsTeamLosing(int32 OwnTeamScore, int32 EnemyTeamScore) const;
	
	bool CanParticipateInNominatedRace(const URacerMatchManager* RacerManagerRef) const;

	FString GetRaceResultText(const ERaceResults RaceResult) const;

	int32 GetRaceResultNumber(const ERaceResults RaceResult) const;

	void DecideMatchWinner(const TObjectPtr<UTeamManager>& HomeTeamManager, const TObjectPtr<UTeamManager>& VisitorTeamManager);

	bool IsTrackCleaningTime(int32 CurrentRace) const;
	
private:

	bool IsJunior(int32 RacerAge) const;

	EPositionTypes GetPositionType(int32 RacerNumber) const;
	
	bool CheckPossibleAmountOfReplacements(int32 AmountOfReplacements, EPositionTypes Position) const;
	
	
	TArray<EPositionTypes> Positions;
	
	TArray<FReplacementRule> ReplacementRules;

	TArray<int32> TrackCleaningRaces {4, 7, 10, 13};
	
	int32 RacersAmount = 12;
	
	int32 JuniorAge = 23;

	int32 MaxAmountOfRaces = 7;

	int32 TeamScoreDifference = 6;
};

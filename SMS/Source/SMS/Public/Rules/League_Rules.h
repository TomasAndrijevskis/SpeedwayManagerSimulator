
#pragma once

#include "CoreMinimal.h"
#include "CompetitionRules.h"
#include "Data/Rules/EPositionTypes.h"
#include "Data/Rules/ReplacementRule.h"
#include "Data/TeamData/ETeams.h"
#include "Data/TeamData/TeamMatchData.h"
#include "League_Rules.generated.h"


class UTeamManager;

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnScoreUpdated, bool, int32, int32);
UCLASS()
class SMS_API ULeague_Rules : public UCompetitionRules
{
	GENERATED_BODY()

public:

	virtual void SetupMatch() override;
	
	void SetTeam(ETeams NewTeam, bool IsVisitor);

	virtual void PopulateRacers() override;

	virtual bool CanStartMatch() const override;

	virtual void MakeRandomRosters() override;
	
	bool IsRacerEligible(int32 RaceLineID, int32 Age) const;
	
	bool CanReplace(const URacerMatchManager* OriginalRacer, const URacerMatchManager* ReplacementRacer, int32 OwnTeamScore, int32 EnemyTeamScore) const;

	bool IsTeamLosing(int32 OwnTeamScore, int32 EnemyTeamScore) const;
	
	bool CanParticipateInNominatedRace(const URacerMatchManager* RacerManagerRef) const;
	
	int32 GetTeamScore(bool IsVisitor) const;

	int32 GetTeamRaceScore(bool IsVisitor, int32 RaceID) const;
	
	TObjectPtr<UTeamManager> GetTeamManager(bool IsVisitor) const;

	FOnScoreUpdated OnScoreUpdatedDelegate;

private:
	
	virtual void CollectRacerStatistics() override;

	virtual void PrepareToEndMatch() override;

	virtual void HandleMatchClosed() override;
	
	virtual void InitializeRules() override;

	virtual void HandleRaceFinished() override;

	void CollectTeamsStatistics();
	
	void InitializeTeam(const FTeamMatchData& TeamData, TObjectPtr<UTeamManager>& OutManager);

	void UpdateScore(bool IsVisitor, int32 PointsToAdd, int32 RaceID);

	bool CheckPossibleAmountOfReplacements(int32 AmountOfReplacements, EPositionTypes Position) const;
	
	bool IsJunior(int32 RacerAge) const {return RacerAge <= JuniorAge;}

	EPositionTypes GetPositionType(int32 RacerNumber) const {return TeamPositions[RacerNumber - 1];}
	
	TObjectPtr<UTeamManager> HomeTeamManager;

	TObjectPtr<UTeamManager> VisitorTeamManager;
	
	TArray<EPositionTypes> TeamPositions;
	
	TArray<FReplacementRule> ReplacementRules;

	int32 LeagueRacersAmount = 12;
	
	int32 JuniorAge = 23;

	int32 MaxAmountOfRaces = 7;

	int32 TeamScoreDifference = 6;
};
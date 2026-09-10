
#pragma once

#include "CoreMinimal.h"
#include "CompetitionRules.h"
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

	void MakeRandomRosters();
	
	int32 GetTeamScore(bool IsVisitor) const;

	int32 GetTeamRaceScore(bool IsVisitor, int32 RaceID) const;
	
	TObjectPtr<UTeamManager> GetTeamManager(bool IsVisitor) const;

	FOnScoreUpdated OnScoreUpdatedDelegate;

private:

	void CollectTeamsStatistics();
	
	virtual void CollectRacerStatistics() override;

	virtual void PrepareToEndMatch() override;

	virtual void HandleMatchClosed() override;
	
	void InitializeTeam(const FTeamMatchData& TeamData, TObjectPtr<UTeamManager>& OutManager);

	void UpdateScore(bool IsVisitor, int32 PointsToAdd, int32 RaceID);
	
	TObjectPtr<UTeamManager> HomeTeamManager;

	TObjectPtr<UTeamManager> VisitorTeamManager;
};
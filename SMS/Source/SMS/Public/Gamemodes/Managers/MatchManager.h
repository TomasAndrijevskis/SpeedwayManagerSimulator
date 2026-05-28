
#pragma once

#include "CoreMinimal.h"
#include "Data/TeamData/TeamRosterData.h"
#include "MatchManager.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMatchStarted, FTeamRosterData*, FTeamRosterData*);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMatchFinished, int, int);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnScoreUpdated, int, int);
UCLASS()
class SMS_API UMatchManager : public UObject
{
	GENERATED_BODY()

public:

	void Init();
	
	void SetTeams(FTeamRosterData* NewHomeTeam, FTeamRosterData* NewVisitorTeam);

	void UpdateScore(int NewHomeTeamScore, int NewVisitorTeamScore);

	int GetHomeTeamScore() const;
	
	int GetVisitorTeamScore() const;
	
	FTeamRosterData& GetHomeTeamData() const;

	FTeamRosterData& GetVisitorTeamData() const;
	
	FOnMatchStarted OnMatchStartedDelegate;

	FOnMatchFinished OnMatchFinishedDelegate;

	FOnScoreUpdated OnScoreUpdatedDelegate;

private:
	
	FTeamRosterData* HomeTeamData;

	FTeamRosterData* VisitorTeamData;

	int HomeTeamScore = 0;

	int VisitorTeamScore = 0;
};

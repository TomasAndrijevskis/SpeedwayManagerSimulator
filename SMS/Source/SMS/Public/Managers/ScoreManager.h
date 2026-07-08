
#pragma once

#include "CoreMinimal.h"
#include "Data/TeamData/TeamMatchData.h"
#include "ScoreManager.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTeamOverallScoreUpdated, int, int);
UCLASS()
class SMS_API UScoreManager : public UObject
{
	GENERATED_BODY()
	
public:

	void AddTeamRef(FTeamMatchData* TeamData);

	int GetTeamScore(bool IsVisitor) const;

	int GetRaceScore(bool IsVisitor) const;
	
	void UpdateScore(int TeamID, int PointsToAdd);

	void ClearLastRaceScore();
	
	FOnTeamOverallScoreUpdated OnTeamOverallScoreUpdatedDelegate;
	
private:

	int HomeOverallScore = 0;

	int VisitorOverallScore = 0;
	
	TArray<FTeamMatchData*> Teams;
};

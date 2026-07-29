
#pragma once

#include "CoreMinimal.h"
#include "Data/TeamData/TeamMatchData.h"
#include "ScoreManager.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTeamOverallScoreUpdated, int32, int32);
UCLASS()
class SMS_API UScoreManager : public UObject
{
	GENERATED_BODY()
	
public:

	void AddTeamRef(FTeamMatchData* TeamData);

	int32 GetTeamScore(bool IsVisitor) const;

	int32 GetRaceScore(bool IsVisitor) const;
	
	void UpdateScore(int32 TeamID, int32 PointsToAdd);

	void ClearLastRaceScore();
	
	FOnTeamOverallScoreUpdated OnTeamOverallScoreUpdatedDelegate;
	
private:

	int32 HomeOverallScore = 0;

	int32 VisitorOverallScore = 0;
	
	TArray<FTeamMatchData*> Teams;
};

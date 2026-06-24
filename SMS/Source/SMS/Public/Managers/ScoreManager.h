
#pragma once

#include "CoreMinimal.h"
#include "ScoreManager.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnOverallScoreUpdated, int, int);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHomePtsUpdated, int);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnVisitorPtsUpdated, int);
UCLASS()
class SMS_API UScoreManager : public UObject
{
	GENERATED_BODY()
	
public:

	void UpdateOverallScore(int AddHomePts, int AddVisitorPts);

	int GetHomeTeamScore() const;
	
	int GetVisitorTeamScore() const;
	
	FOnOverallScoreUpdated OnOverallScoreUpdatedDelegate;

	FOnHomePtsUpdated OnHomePtsUpdatedDelegate;
	
	FOnVisitorPtsUpdated OnVisitorPtsUpdatedDelegate;
	
private:

	int HomeOverallScore = 0;

	int VisitorOverallScore = 0;

};

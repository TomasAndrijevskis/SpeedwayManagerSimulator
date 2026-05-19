
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PointsManager.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnScoreChanged, int, int);
UCLASS()
class SMS_API UPointsManager : public UObject
{
	GENERATED_BODY()

		
public:

	void UpdateOverallScore(int HomeAddPoints, int VisitorAddPoints);

	FOnScoreChanged OnScoreChangedDelegate;
	
private:
	
	int HomeOverallPoints = 0;

	int VisitorOverallPoints = 0;
};

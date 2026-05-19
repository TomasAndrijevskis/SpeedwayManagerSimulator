
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreCounter.generated.h"


class UPointsManager;
class UNumbersBox;

UCLASS()
class SMS_API UScoreCounter : public UUserWidget
{
	GENERATED_BODY()

public:
	
	void SetRacePoints(int NewHomePoints, int NewVisitorPoints);

	void SetOverallScore(int NewHomePoints, int NewVisitorPoints);

protected:

	virtual void NativeConstruct() override;
	
private:

	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_HomeTeamRacePoints;

	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_HomeTeamOverallPoints;
	
	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_VisitorTeamRacePoints;
	
	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_VisitorTeamOverallPoints;

	UPROPERTY()
	UPointsManager* PointsManager;
};

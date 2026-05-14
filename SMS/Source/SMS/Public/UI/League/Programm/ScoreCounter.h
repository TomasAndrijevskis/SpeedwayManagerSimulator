
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreCounter.generated.h"


class UTextBlock;

UCLASS()
class SMS_API UScoreCounter : public UUserWidget
{
	GENERATED_BODY()

public:

private:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_HomeTeamRacePoints;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_VisitorTeamRacePoints;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_HomeTeamOverallPoints;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_VisitorTeamOverallPoints;
	
};

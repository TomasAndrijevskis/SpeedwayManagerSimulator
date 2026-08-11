
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StandingsLine.generated.h"

class UNamesBox;
class UNumbersBox;

UCLASS()
class SMS_API UStandingsLine : public UUserWidget
{
	GENERATED_BODY()

public:

private:

	//void SetRank(const int32 NewAmount);
	
	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_Rank;

	UPROPERTY(meta = (BindWidget))
	UNamesBox* NamesBox_TeamName;

	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_Matches;

	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_Wins;

	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_Losses;

	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_Draws;

	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_Bonuses;

	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_Difference;

	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_Points;
};


#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatisticsLine.generated.h"


class UNamesBox;
class UNumbersBox;

UCLASS()
class SMS_API UStatisticsLine : public UUserWidget
{
	GENERATED_BODY()

public:

	void InitializeLine(int32 NewID);

	int32 GetRacerID() const;
	
private:

	UPROPERTY(meta=(BindWidget))
	UNumbersBox* NumbersBox_Position;

	UPROPERTY(meta=(BindWidget))
	UNamesBox* NamesBox_Name;

	UPROPERTY(meta=(BindWidget))
	UNamesBox* NamesBox_Team;

	UPROPERTY(meta=(BindWidget))
	UNamesBox* NamesBox_Status;

	UPROPERTY(meta=(BindWidget))
	UNumbersBox* NumbersBox_Matches;
	
	UPROPERTY(meta=(BindWidget))
	UNumbersBox* NumbersBox_Races;
	
	UPROPERTY(meta=(BindWidget))
	UNumbersBox* NumbersBox_Points;

	UPROPERTY(meta=(BindWidget))
	UNumbersBox* NumbersBox_Bonuses;

	UPROPERTY(meta=(BindWidget))
	UNumbersBox* NumbersBox_FirstPlace;
	
	UPROPERTY(meta=(BindWidget))
	UNumbersBox* NumbersBox_SecondPlace;
	
	UPROPERTY(meta=(BindWidget))
	UNumbersBox* NumbersBox_ThirdPlace;
	
	UPROPERTY(meta=(BindWidget))
	UNumbersBox* NumbersBox_FourthPlace;

	UPROPERTY(meta=(BindWidget))
	UNumbersBox* NumbersBox_DidNotFinish;
	
	UPROPERTY(meta=(BindWidget))
	UNumbersBox* NumbersBox_AveragePointsPerRace;

	UPROPERTY(meta=(BindWidget))
	UNumbersBox* NumbersBox_AveragePointsPerMatch;

	UPROPERTY(meta=(BindWidget))
	UNumbersBox* NumbersBox_AveragePointsHome;

	UPROPERTY(meta=(BindWidget))
	UNumbersBox* NumbersBox_AveragePointsAway;

	int32 RacerID;
};

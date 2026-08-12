
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/RacersData/RacerStatistics.h"
#include "StatisticsLine.generated.h"


class UNamesBox;
class UNumbersBox;

UCLASS()
class SMS_API UStatisticsLine : public UUserWidget
{
	GENERATED_BODY()

public:

	void InitializeLine(const FRacerStatistics& RacerStats);

	float GetRacerAverage() const;

	void SetRank(const int32 NewRank);
	
private:

	UPROPERTY(meta=(BindWidget))
	UNumbersBox* NumbersBox_Rank;

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
	UNumbersBox* NumbersBox_OverallPoints;
	
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
	
	void SetNumbers(const TArray<FMatchStatistics>& MatchStatistics);
	
	void SetName(const FString& NewName);

	void SetTeam(const FString& NewName);

	void SetStatus(const int32 NewAge);

	void SetMatches(const int32 NewAmount);

	void SetRaces(const int32 NewAmount);

	void SetBonuses(const int32 NewAmount);

	void SetPoints(const int32 NewAmount);

	void SetOverallPoints(const int32 NewAmount);
	
	void SetNotFinishedRaces(const int32 NewAmount);

	void SetPlaces(const int32 FirstAmount, const int32 SecondAmount, const int32 ThirdAmount ,const int32 FourthAmount);

	void SetAveragePointsPerRace(const int32 Points, const int32 Races);

	void SetAveragePointsPerMatch(const int32 Points, const int32 Matches);

	void SetAveragePointsPerRaceHome(const int32 Points, const int32 Races);

	void SetAveragePointsPerRaceAway(const int32 Points, const int32 Races);

	float AvgP = 0.f;
};
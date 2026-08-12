
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/TeamData/TeamStatistics.h"
#include "StandingsLine.generated.h"

class UNamesBox;
class UNumbersBox;

UCLASS()
class SMS_API UStandingsLine : public UUserWidget
{
	GENERATED_BODY()

public:

	void InitializeStandingsLine(const FTeamStatistics& TeamStatistics);

	int32 GetTeamPoints() const;

	int32 GetMatchesAmount() const;

	int32 GetWins() const;

	int32 GetDifference() const;
	
	void SetRank(const int32 NewAmount);
	
private:

	void SetNumbers(const FTeamStatistics& TeamStatistics);

	void SetTeamName(const FString& TeamName);

	void SetMatches(const int32 NewAmount);

	void SetWins(const int32 NewAmount);

	void SetLosses(const int32 NewAmount);

	void SetDraws(const int32 NewAmount);

	void SetBonuses(const int32 NewAmount);

	void SetDifference(const int32 NewAmount);

	void SetPoints(const int32 NewAmount);
	
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

	int32 Points = 0;

	int32 Matches = 0;

	int32 Wins = 0;

	int32 Difference = 0;
};

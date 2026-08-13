
#include "UI/League/Standings/StandingsLine.h"
#include "UI/BaseClasses/NamesBox.h"
#include "UI/BaseClasses/NumbersBox.h"


void UStandingsLine::InitializeStandingsLine(const FTeamStatistics& TeamStatistics)
{
	SetTeamName(TeamStatistics.TeamName);
	SetNumbers(TeamStatistics);
}

void UStandingsLine::SetNumbers(const FTeamStatistics& TeamStatistics)
{
	int32 Losses = 0;
	int32 Draws = 0;
	TMap<int32, TArray<int32>> OpponentResults;
	TMap<int32, TArray<int32>> TeamResults;
	for (const auto& MatchStats : TeamStatistics.MatchStatistics)
	{
		Matches++;
		if (MatchStats.Result == EMatchResults::Win)
		{
			Wins++;
			Points += 2;
		}
		if (MatchStats.Result == EMatchResults::Loss)
		{
			Losses++;
		}
		if (MatchStats.Result == EMatchResults::Draw)
		{
			Draws++;
			Points++;
		}
		for (const auto& Results : MatchStats.OpponentResult)
		{
			Difference += MatchStats.TeamScore - Results.Value;
			OpponentResults.FindOrAdd(Results.Key).Add(Results.Value);
			TeamResults.FindOrAdd(Results.Key).Add(MatchStats.TeamScore);
		}
	}
	const int32 Bonuses = CalculateBonus(TeamResults, OpponentResults);
	SetWins(Wins);
	SetLosses(Losses);
	SetDraws(Draws);
	SetBonuses(Bonuses);
	SetPoints(Points + Bonuses);
	SetMatches(Matches);
	SetDifference(Difference);
}


void UStandingsLine::SetTeamName(const FString& TeamName)
{
	NamesBox_TeamName->SetText(TeamName);
}

int32 UStandingsLine::CalculateBonus(TMap<int32, TArray<int32>>& TeamResults, TMap<int32, TArray<int32>>& OpponentResults)
{
	int32 Bonuses = 0;
	for (const auto& OpponentResult : OpponentResults)
	{
		int32 OpponentResultsSum = 0;
		int32 TeamResultsSum = 0;
		int32 MatchesAgainstSameTeam = OpponentResult.Value.Num();
		if (MatchesAgainstSameTeam == 2)
		{
			for (const auto& Result : OpponentResult.Value)
			{
				OpponentResultsSum += Result;
			}
			for (const auto& TeamResult : TeamResults)
			{
				if (TeamResult.Key == OpponentResult.Key)
				{
					for (const auto& Result : TeamResult.Value)
					{
						TeamResultsSum += Result;
					}
				}
			}
			if (TeamResultsSum > OpponentResultsSum) Bonuses++;
		}
	}
	OpponentResults.Empty();
	TeamResults.Empty();
	return Bonuses;
}

void UStandingsLine::SetRank(const int32 NewAmount)
{
	NumbersBox_Rank->SetText(NewAmount);
}


void UStandingsLine::SetMatches(const int32 NewAmount)
{
	NumbersBox_Matches->SetText(NewAmount);
}

void UStandingsLine::SetWins(const int32 NewAmount)
{
	NumbersBox_Wins->SetText(NewAmount);
}

void UStandingsLine::SetLosses(const int32 NewAmount)
{
	NumbersBox_Losses->SetText(NewAmount);
}

void UStandingsLine::SetDraws(const int32 NewAmount)
{
	NumbersBox_Draws->SetText(NewAmount);
}

void UStandingsLine::SetBonuses(const int32 NewAmount)
{
	NumbersBox_Bonuses->SetText(NewAmount);
}

void UStandingsLine::SetDifference(const int32 NewAmount)
{
	NumbersBox_Difference->SetText(NewAmount);
}

void UStandingsLine::SetPoints(const int32 NewAmount)
{
	NumbersBox_Points->SetText(NewAmount);
}

int32 UStandingsLine::GetTeamPoints() const{return Points;}
int32 UStandingsLine::GetMatchesAmount() const{return Matches;}
int32 UStandingsLine::GetWins() const{return Wins;}
int32 UStandingsLine::GetDifference() const{return Difference;}

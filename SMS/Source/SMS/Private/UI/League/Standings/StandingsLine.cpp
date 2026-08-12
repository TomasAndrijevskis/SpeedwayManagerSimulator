
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
	//int32 Bonuses = 0;
	for (const auto& MatchStats : TeamStatistics.MatchStatistics)
	{
		Matches++;
		if (MatchStats.MatchResult == EMatchResults::Win)
		{
			Wins++;
			Points += 2;
		}
		if (MatchStats.MatchResult == EMatchResults::Loss)
		{
			Losses++;
		}
		if (MatchStats.MatchResult == EMatchResults::Draw)
		{
			Draws++;
			Points++;
		}
		Difference += MatchStats.TeamScore - MatchStats.OpponentData.OpponentTeamScore;
	}
	SetWins(Wins);
	SetLosses(Losses);
	SetDraws(Draws);
	SetPoints(Points);
	SetMatches(Matches);
	SetDifference(Difference);
	//SetBonuses(Bonuses);
}

void UStandingsLine::SetRank(const int32 NewAmount)
{
	NumbersBox_Rank->SetText(NewAmount);
}

void UStandingsLine::SetTeamName(const FString& TeamName)
{
	NamesBox_TeamName->SetText(TeamName);
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


#include "UI/League/Statistics/StatisticsLine.h"
#include "Subsystems/RulesSubsystem.h"
#include "UI/BaseClasses/NamesBox.h"
#include "UI/BaseClasses/NumbersBox.h"


void UStatisticsLine::InitializeLine(const FRacerStatistics& RacerStats)
{
	SetName(RacerStats.RacerName);
	SetTeam(RacerStats.TeamName);
	SetStatus(RacerStats.RacerAge);
	SetMatches(RacerStats.MatchStatistics.Num());
	SetNumbers(RacerStats.MatchStatistics);
}


void UStatisticsLine::SetRank(const int32 NewRank)
{
	NumbersBox_Rank->SetText(NewRank);
}


void UStatisticsLine::SetName(const FString& NewName)
{
	NamesBox_Name->SetText(NewName);
}

void UStatisticsLine::SetTeam(const FString& NewName)
{
	NamesBox_Team->SetText(NewName);
}

void UStatisticsLine::SetStatus(const int32 NewAge)
{
	if (NewAge <= 23) NamesBox_Status->SetText("Junior");
	if (NewAge > 23 && NewAge <= 26) NamesBox_Status->SetText("U26");
	if (NewAge > 26) NamesBox_Status->SetText("Senior");
}

void UStatisticsLine::SetMatches(const int32 NewAmount)
{
	NumbersBox_Matches->SetText(NewAmount);
}

void UStatisticsLine::SetNumbers(const TArray<FMatchStatistics>& MatchStatistics)
{
	int32 Races = 0;
	int32 Points = 0;
	int32 DNF = 0;
	int32 First = 0;
	int32 Second = 0;
	int32 Third = 0;
	int32 Fourth = 0;
	int32 PointsHome = 0;
	int32 PointsAway = 0;
	int32 RacesHome = 0;
	int32 RacesAway = 0;
	int32 BonusesHome = 0;
	int32 BonusesAway = 0;
	if (URulesSubsystem* Rules = GetWorld()->GetGameInstance()->GetSubsystem<URulesSubsystem>())
	{
		for (const auto& Stats : MatchStatistics)
		{
			Races += Stats.RaceResults.Num();
			if (Stats.bIsVisitor) BonusesAway += Stats.Bonuses;
			else BonusesHome += Stats.Bonuses;
			
			for (const auto& Result : Stats.RaceResults)
			{
				Points += Rules->GetRaceResultNumber(Result);
				if (Result == ERaceResults::First) First++;
				if (Result == ERaceResults::Second) Second++;
				if (Result == ERaceResults::Third) Third++;
				if (Result == ERaceResults::Fourth) Fourth++;
				if (Result == ERaceResults::Defect) DNF++;

				if (Stats.bIsVisitor)
				{
					PointsAway += Rules->GetRaceResultNumber(Result);
					RacesAway++;
				}
				else
				{
					PointsHome += Rules->GetRaceResultNumber(Result);
					RacesHome++;
				}
			}
		}
	}
	int32 Bonuses = BonusesHome + BonusesAway;
	SetRaces(Races);
	SetBonuses(Bonuses);
	SetPoints(Points);
	SetOverallPoints(Points + Bonuses);
	SetNotFinishedRaces(DNF);
	SetPlaces(First, Second, Third, Fourth);
	SetAveragePointsPerRace(Points + Bonuses, Races);
	SetAveragePointsPerMatch(Points + Bonuses, MatchStatistics.Num());
	SetAveragePointsPerRaceHome(PointsHome + BonusesHome, RacesHome);
	SetAveragePointsPerRaceAway(PointsAway + BonusesAway, RacesAway);
}

void UStatisticsLine::SetPoints(const int32 NewAmount)
{
	NumbersBox_Points->SetText(NewAmount);
}

void UStatisticsLine::SetOverallPoints(const int32 NewAmount)
{
	NumbersBox_OverallPoints->SetText(NewAmount);
}

void UStatisticsLine::SetNotFinishedRaces(const int32 NewAmount)
{
	NumbersBox_DidNotFinish->SetText(NewAmount);
}


void UStatisticsLine::SetPlaces(const int32 FirstAmount, const int32 SecondAmount, const int32 ThirdAmount, const int32 FourthAmount)
{
	NumbersBox_FirstPlace->SetText(FirstAmount);
	NumbersBox_SecondPlace->SetText(SecondAmount);
	NumbersBox_ThirdPlace->SetText(ThirdAmount);
	NumbersBox_FourthPlace->SetText(FourthAmount);
}

void UStatisticsLine::SetAveragePointsPerRace(const int32 Points, const int32 Races)
{
	AvgP = static_cast<float>(Points) / static_cast<float>(Races);
	NumbersBox_AveragePointsPerRace->SetText(AvgP);
}

void UStatisticsLine::SetAveragePointsPerMatch(const int32 Points, const int32 Matches)
{
	float Result = static_cast<float>(Points) / static_cast<float>(Matches); 
	NumbersBox_AveragePointsPerMatch->SetText(Result);
}

void UStatisticsLine::SetAveragePointsPerRaceHome(const int32 Points, const int32 Races)
{
	if (Races == 0)
	{
		NumbersBox_AveragePointsHome->SetText("");
		return;
	}
	float Result = static_cast<float>(Points) / static_cast<float>(Races); 
	NumbersBox_AveragePointsHome->SetText(Result);
}

void UStatisticsLine::SetAveragePointsPerRaceAway(const int32 Points, const int32 Races)
{
	if (Races == 0)
	{
		NumbersBox_AveragePointsAway->SetText("");
		return;
	}
	float Result = static_cast<float>(Points) / static_cast<float>(Races);
	NumbersBox_AveragePointsAway->SetText(Result);
}


void UStatisticsLine::SetRaces(const int32 NewAmount)
{
	NumbersBox_Races->SetText(NewAmount);
}

void UStatisticsLine::SetBonuses(const int32 NewAmount)
{
	NumbersBox_Bonuses->SetText(NewAmount);
}

float UStatisticsLine::GetRacerAverage() const {return AvgP;}
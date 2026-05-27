
#include "SMS/Public/UI/League/Program/ScoreCounter.h"
#include "UI/BaseClasses/NumbersBox.h"


void UScoreCounter::SetRacePoints(int NewHomePoints, int NewVisitorPoints)
{
	NumbersBox_HomeTeamRacePoints->SetText(NewHomePoints);
	NumbersBox_VisitorTeamRacePoints->SetText(NewVisitorPoints);
}


void UScoreCounter::SetOverallScore(int NewHomePoints, int NewVisitorPoints)
{
	NumbersBox_HomeTeamOverallPoints->SetText(NewHomePoints);
	NumbersBox_VisitorTeamOverallPoints->SetText(NewVisitorPoints);
}

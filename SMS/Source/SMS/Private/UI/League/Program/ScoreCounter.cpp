
#include "SMS/Public/UI/League/Program/ScoreCounter.h"
#include "UI/BaseClasses/NumbersBox.h"


void UScoreCounter::SetRacePoints(int32 NewHomePoints, int32 NewVisitorPoints)
{
	NumbersBox_HomeTeamRacePoints->SetText(NewHomePoints);
	NumbersBox_VisitorTeamRacePoints->SetText(NewVisitorPoints);
}


void UScoreCounter::SetOverallScore(int32 NewHomePoints, int32 NewVisitorPoints)
{
	NumbersBox_HomeTeamOverallPoints->SetText(NewHomePoints);
	NumbersBox_VisitorTeamOverallPoints->SetText(NewVisitorPoints);
}

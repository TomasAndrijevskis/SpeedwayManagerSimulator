
#include "UI/League/Statistics/StatisticsLine.h"
#include "UI/BaseClasses/NumbersBox.h"


void UStatisticsLine::InitializeLine(int32 NewID)
{
	RacerID = NewID;
	NumbersBox_Position->SetText(RacerID);
}


int32 UStatisticsLine::GetRacerID() const
{
	return RacerID;
}

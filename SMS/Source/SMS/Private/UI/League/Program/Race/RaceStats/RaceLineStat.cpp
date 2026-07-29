
#include "UI/League/Program/Race/RaceStats/RaceLineStat.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "UI/BaseClasses/NumbersBox.h"


void URaceLineStat::SetID(int32 RaceLineID)
{
	ID = RaceLineID;
	NumbersBox_RaceLine->SetText(ID + 1);
}


void URaceLineStat::UpdateNumbers(int32 PointsToAdd)
{
	CurrentPoints += PointsToAdd;
	TextBlock_PointsAmount->SetText(FText::AsNumber(CurrentPoints));
}


void URaceLineStat::UpdateProgressBar(int32 OverallPoints)
{
	float NewPercent = 0.f;
	if (CurrentPoints != 0) NewPercent = static_cast<float>(CurrentPoints) / OverallPoints;
	ProgressBar->SetPercent(NewPercent);
}


int32 URaceLineStat::GetID() const{return ID;}

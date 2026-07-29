
#include "UI/League/Program/Race/RaceStats/RaceLineStat.h"
#include "Components/ProgressBar.h"
#include "UI/BaseClasses/NumbersBox.h"


void URaceLineStat::SetID(int32 RaceLineID)
{
	ID = RaceLineID;
	NumbersBox_RaceLine->SetText(ID + 1);
}


void URaceLineStat::UpdateNumbers(int PointsToAdd)
{
	CurrentPoints += PointsToAdd;
	float NewPercent = CurrentPoints / AmountOfRaceLines / 100.0f;
	UE_LOG(LogTemp, Warning, TEXT("New percent %f"), NewPercent);
	ProgressBar->SetPercent(NewPercent);
}

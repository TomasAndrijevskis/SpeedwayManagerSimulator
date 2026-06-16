
#include "Managers/RacerManager.h"


void URacerManager::Init(int NewRacerNumber, const FRacerData& RacerData)
{
	RacerNumber = NewRacerNumber;
	Data = RacerData;
}


void URacerManager::AddPoints(const FString& NewPoints)
{
	if (!CanAddNewPointBox()) return;
	RacerPoints.Add(NewPoints);
	OnPointsAddedDelegate.Broadcast(NewPoints);
}


int URacerManager::CountOverallPoints(bool CanCount)
{
	if (!CanCount) return 0;
	int sum = 0;
	for (const auto& Element : RacerPoints)
	{
		int Number = FCString::Atoi(*Element);
		sum += Number;
	}
	return sum;
}


bool URacerManager::CanAddNewPointBox() const
{
	if (RacerPoints.Num() < MaxRacesAmount) return true;
	return false;
}


#include "Managers/RacerManager.h"


void URacerManager::Initialize(int NewRacerNumber, const FRacerData& RacerData)
{
	RacerNumber = NewRacerNumber;
	Data = RacerData;
	if (RacerNumber <= 6) bIsVisitor = false;
	else bIsVisitor = true;
	UE_LOG(LogTemp, Warning, TEXT("Number: %i, Name: %s"), NewRacerNumber, *RacerData.Name);
	UE_LOG(LogTemp, Warning, TEXT("IsVisitor: %i"), bIsVisitor);
	UE_LOG(LogTemp, Display, TEXT("-----"));
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


bool URacerManager::IsVisitor() const{return bIsVisitor;}
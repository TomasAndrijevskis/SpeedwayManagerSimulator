
#include "Managers/RacerManager.h"


void URacerManager::Initialize(const FRacerMatchData& RacerData)
{
	Data = RacerData;
}


void URacerManager::CalculateRating(bool IsVisitor)
{
	int Defect = FMath::RandRange(1, 20);
	if (Defect == 1)
	{
		CurrentRacerRating = 0;
		return;
	}
	int Start = FMath::RandRange(0,5);
	int Driving = FMath::RandRange(0,10);
	if (!IsVisitor) Driving += FMath::RandRange(0,2);
	int RacerRating = Data.RacerData.RacerStats.Rating;
	CurrentRacerRating = Start + Driving + RacerRating;
	
	UE_LOG(LogTemp, Warning, TEXT("Name: %s"), *Data.RacerData.Name);
	UE_LOG(LogTemp, Warning, TEXT("TieBreaker: %i"), TieBreakerValue);
	UE_LOG(LogTemp, Warning, TEXT("Start rating: %i"), Start);
	UE_LOG(LogTemp, Warning, TEXT("Driving rating: %i"), Driving);
	UE_LOG(LogTemp, Warning, TEXT("Race rating: %i"), CurrentRacerRating);
	UE_LOG(LogTemp, Display, TEXT("-----"));
}


void URacerManager::SetTieBreaker()
{
	TieBreakerValue = FMath::RandRange(1,100);
}


void URacerManager::AddPoints(const FString& NewPoints, bool AddBonus)
{
	if (!CanAddNewPointBox()) return;
	RacerPoints.Add(NewPoints);
	OnPointsAddedDelegate.Broadcast(NewPoints, AddBonus);
}


int URacerManager::CountOverallPoints()
{
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


int URacerManager::GetTieBreaker() const {return TieBreakerValue;}
int URacerManager::GetCurrentRaceRating() const {return CurrentRacerRating;}
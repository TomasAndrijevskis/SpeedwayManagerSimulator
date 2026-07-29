
#include "Managers/RacerManager.h"
#include "UI/League/Program/Race/RaceLineBase.h"


void URacerManager::Initialize(const FRacerMatchData& RacerData)
{
	Data = RacerData;
}


void URacerManager::CalculateRating(bool IsVisitor)
{
	int32 Defect = FMath::RandRange(1, 20);
	if (Defect == 1)
	{
		CurrentRacerRating = 0;
		return;
	}
	int32 Start = FMath::RandRange(0,5);
	int32 Driving = FMath::RandRange(0,10);
	if (!IsVisitor) Driving += FMath::RandRange(0,2);
	int32 RacerRating = Data.GetBaseRating();
	CurrentRacerRating = Start + Driving + RacerRating;
	
	UE_LOG(LogTemp, Warning, TEXT("Name: %s"), *Data.RacerData.Name);
	UE_LOG(LogTemp, Warning, TEXT("TieBreaker: %i"), TieBreakerValue);
	UE_LOG(LogTemp, Warning, TEXT("Start rating: %i"), Start);
	UE_LOG(LogTemp, Warning, TEXT("Driving rating: %i"), Driving);
	UE_LOG(LogTemp, Warning, TEXT("Race rating: %i"), CurrentRacerRating);
	UE_LOG(LogTemp, Display, TEXT("-----"));
}


void URacerManager::AddParticipatedRace(URaceLineBase* RaceLineRef)
{
	if (!ParticipatedRacesRef.Contains(RaceLineRef)) ParticipatedRacesRef.Add(RaceLineRef);
}


void URacerManager::RemoveParticipatedRace(URaceLineBase* RaceLineRef)
{
	if (ParticipatedRacesRef.Contains(RaceLineRef))
	{
		RaceLineRef->OnRaceStartedDelegate.RemoveAll(this);
		ParticipatedRacesRef.Remove(RaceLineRef);
	}
}


void URacerManager::OnRaceStarted()
{
	SetTieBreaker();
	CalculateRating(IsVisitor());
}


void URacerManager::SetTieBreaker()
{
	TieBreakerValue = FMath::RandRange(1,100);
}


void URacerManager::AddPoints(const FString& NewPoints, bool AddBonus)
{
	RacerPoints.Add(NewPoints);
	if (AddBonus) RacerBonuses++;
	OnPointsAddedDelegate.Broadcast(NewPoints, AddBonus);
}


int32 URacerManager::CountOverallPoints()
{
	int32 sum = 0;
	for (const auto& Element : RacerPoints)
	{
		int32 Number = FCString::Atoi(*Element);
		sum += Number;
	}
	return sum;
}


void URacerManager::SetParticipatedInNominatedRace(bool NewParticipated){bParticipatedInNominatedRace = NewParticipated;}
int32 URacerManager::GetTieBreaker() const {return TieBreakerValue;}
int32 URacerManager::GetCurrentRaceRating() const {return CurrentRacerRating;}
int32 URacerManager::GetBonusAmount() const {return RacerBonuses;}
int32 URacerManager::GetParticipatedRacesAmount() const {return ParticipatedRacesRef.Num();}
int32 URacerManager::GetRacerNumber() const {return Data.RacerNumber;}
int32 URacerManager::GetRacerAge() const {return Data.GetRacerAge();}
bool URacerManager::CanDriveMore(int32 MaxAmountOfRaces) const {return ParticipatedRacesRef.Num() < MaxAmountOfRaces;}
bool URacerManager::DidParticipateInNominatedRace() const {return bParticipatedInNominatedRace;}
bool URacerManager::IsVisitor() const {return Data.IsVisitor();}
FString URacerManager::GetRacerName() const {return Data.GetRacerName();}
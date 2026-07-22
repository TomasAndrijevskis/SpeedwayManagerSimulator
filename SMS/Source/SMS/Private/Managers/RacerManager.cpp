
#include "Managers/RacerManager.h"
#include "UI/League/Program/RaceLineBase.h"


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
	int RacerRating = Data.GetBaseRating();
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
	CalculateRating(Data.IsVisitor());
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


void URacerManager::SetParticipatedInNominatedRace(bool NewParticipated){bParticipatedInNominatedRace = NewParticipated;}
int URacerManager::GetTieBreaker() const {return TieBreakerValue;}
int URacerManager::GetCurrentRaceRating() const {return CurrentRacerRating;}
int URacerManager::GetBonusAmount() const{return RacerBonuses;}
int URacerManager::GetRacerNumber() const{return Data.RacerNumber;}
bool URacerManager::ParticipatedInNominatedRace() const{return bParticipatedInNominatedRace;}
bool URacerManager::CanDriveMore() const {return ParticipatedRacesRef.Num() < MaxRacesAmount;}
bool URacerManager::IsJunior() const {return Data.IsJunior();}
bool URacerManager::IsReplacement() const{return Data.IsReplacement();}
bool URacerManager::IsVisitor() const{return Data.IsVisitor();}
FString URacerManager::GetRacerName() const{return Data.GetRacerName();}


#include "Managers/RacerManager.h"
#include "Managers/MatchManager.h"
#include "Subsystems/OverallRacerStatsSubsystem.h"
#include "Subsystems/RulesSubsystem.h"
#include "UI/League/Program/Race/RaceLineBase.h"


void URacerManager::Initialize(const FRacerMatchData& RacerData)
{
	Data = RacerData;
}


void URacerManager::CalculateRating(bool IsVisitor, float GateModifier, float DistanceModifier)
{
	int32 Defect = FMath::RandRange(1, 20);
	if (Defect == 1)
	{
		CurrentRacerRating = 0;
		return;
	}
	int32 RacerRating = Data.GetBaseRating();
	UE_LOG(LogTemp, Display, TEXT("-----"));
	UE_LOG(LogTemp, Display, TEXT("Name: %s"), *Data.RacerData.Name);
	UE_LOG(LogTemp, Display, TEXT("Rating %i"), RacerRating);
	//UE_LOG(LogTemp, Display, TEXT("TieBreaker: %i"), TieBreakerValue);
	
	float Start = FMath::RandRange(0,5);
	UE_LOG(LogTemp, Warning, TEXT("Start %f"), Start);
	float StartModifier = Start * GateModifier;
	UE_LOG(LogTemp, Error, TEXT("Start modified: %f - Modifier: %f"), StartModifier, GateModifier);
	
	float Driving = FMath::RandRange(0,10);
	if (!IsVisitor) Driving += FMath::RandRange(0,2);
	UE_LOG(LogTemp, Warning, TEXT("Driving %f"), Driving);
	float DrivingModifier = Driving * DistanceModifier;
	UE_LOG(LogTemp, Error, TEXT("Driving modified: %f - Modifier: %f"), DrivingModifier, DistanceModifier);

	
	CurrentRacerRating = Start + StartModifier + Driving + DrivingModifier + RacerRating;
	UE_LOG(LogTemp, Display, TEXT("Race rating: %f"), CurrentRacerRating);
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


void URacerManager::OnRaceStarted(float GateModifier, float DistanceModifier)
{
	SetTieBreaker();
	CalculateRating(IsVisitor(), GateModifier, DistanceModifier);
}


void URacerManager::SetTieBreaker()
{
	TieBreakerValue = FMath::RandRange(1,100);
}


void URacerManager::AddPoints(const ERaceResults NewResult, bool AddBonus)
{
	RacerPoints.Add(NewResult);
	if (AddBonus) RacerBonuses++;
	OnPointsAddedDelegate.Broadcast(NewResult, AddBonus);
}


int32 URacerManager::CountOverallPoints()
{
	int32 sum = 0;
	if (URulesSubsystem* Rules = GetWorld()->GetGameInstance()->GetSubsystem<URulesSubsystem>())
	{
		for (const auto& Point : RacerPoints)
		{
			int32 Number = Rules->GetRaceResultNumber(Point);
			sum += Number;
		}
	}
	return sum;
}


void URacerManager::CollectMatchStatistics()
{
	if (UOverallStatsSubsystem* Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UOverallStatsSubsystem>())
	{
		FRacerStatistics NewStats;
		NewStats.RacerID = Data.GetRacerID();
		NewStats.RacerName = Data.GetRacerName();
		NewStats.RacerAge = Data.GetRacerAge();
		NewStats.Team = Data.GetRacerTeamName();
		FMatchStatistics NewMatchStats;
		NewMatchStats.bIsVisitor = IsVisitor();
		NewMatchStats.RaceResults = RacerPoints;
		NewMatchStats.Bonuses = RacerBonuses;
		NewStats.MatchStatistics.Add(NewMatchStats);
		Subsystem->AddStat(NewStats);
	}
}


void URacerManager::SetParticipatedInNominatedRace(bool NewParticipated){bParticipatedInNominatedRace = NewParticipated;}
void URacerManager::IncreaseAmountOfReplacements(){AmountOfReplacements++;}
void URacerManager::DecreaseAmountOfReplacements(){AmountOfReplacements--;}
int32 URacerManager::GetAmountOfReplacements() const{return AmountOfReplacements;}
int32 URacerManager::GetTieBreaker() const {return TieBreakerValue;}
int32 URacerManager::GetBonusAmount() const {return RacerBonuses;}
int32 URacerManager::GetParticipatedRacesAmount() const {return ParticipatedRacesRef.Num();}
int32 URacerManager::GetRacerNumber() const {return Data.RacerNumber;}
int32 URacerManager::GetRacerAge() const {return Data.GetRacerAge();}
float URacerManager::GetCurrentRaceRating() const {return CurrentRacerRating;}
bool URacerManager::CanDriveMore(int32 MaxAmountOfRaces) const {return ParticipatedRacesRef.Num() < MaxAmountOfRaces;}
bool URacerManager::DidParticipateInNominatedRace() const {return bParticipatedInNominatedRace;}
bool URacerManager::IsVisitor() const {return Data.IsVisitor();}
FString URacerManager::GetRacerName() const {return Data.GetRacerName();}
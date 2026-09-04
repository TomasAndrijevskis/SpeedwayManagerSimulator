
#include "Managers/RacerManager.h"
#include "Subsystems/OverallRacerStatsSubsystem.h"
#include "Subsystems/RulesSubsystem.h"
#include "UI/League/Program/Race/League_RaceLine_Base.h"


void URacerManager::Initialize(const FRacerMatchData& RacerData)
{
	Data = RacerData;
}


void URacerManager::CalculateRating(float GateModifier, float DistanceModifier, ETrackTypes TrackType)
{
	SetTieBreaker();
	UE_LOG(LogTemp, Error, TEXT("================================================"));
	UE_LOG(LogTemp, Display, TEXT("Name: %s"), *Data.RacerData.Name);
	int32 Defect = FMath::RandRange(1, 20);
	if (Defect == 1)
	{
		UE_LOG(LogTemp, Display, TEXT("defect"));
		CurrentRacerRating = 0;
		return;
	}
	int32 RacerRating = Data.GetBaseRating();
	UE_LOG(LogTemp, Display, TEXT("Rating %i"), RacerRating);
	//UE_LOG(LogTemp, Display, TEXT("TieBreaker: %i"), TieBreakerValue);

	int32 Luck = FMath::RandRange(-3, 3);
	float Start = Data.GetReaction();
	UE_LOG(LogTemp, Warning, TEXT("initial Start %f"), Start);
	UE_LOG(LogTemp, Warning, TEXT("Luck %i"), Luck);
	UE_LOG(LogTemp, Error, TEXT("Modifier: %f"), GateModifier);
	Start += Luck;
	Start += GateModifier * 10;
	UE_LOG(LogTemp, Error, TEXT("Final start value %f"), Start);
	UE_LOG(LogTemp, Display, TEXT("-----"));
	
	float DrivingSkill = Data.GetDrivingSkill(TrackType);
	UE_LOG(LogTemp, Warning, TEXT("Driving %f"), DrivingSkill);
	UE_LOG(LogTemp, Error, TEXT("Modifier: %f"), DistanceModifier);
	if (!IsVisitor())
	{
		int32 TrackKnowledge = FMath::RandRange(0,3);
		UE_LOG(LogTemp, Warning, TEXT("Track Knowledge %i"), TrackKnowledge);
		DrivingSkill += TrackKnowledge;
	}
	
	DrivingSkill += DistanceModifier * 10;
	UE_LOG(LogTemp, Error, TEXT("Final driving value %f"), DrivingSkill);
	UE_LOG(LogTemp, Display, TEXT("-----"));

	
	CurrentRacerRating = RacerRating * .4 + Start *.3 + DrivingSkill * .3;
	UE_LOG(LogTemp, Display, TEXT("Final Race rating: %f"), CurrentRacerRating);
}


void URacerManager::AddParticipatedRace(URaceLine_Base* RaceLineRef)
{
	if (!ParticipatedRacesRef.Contains(RaceLineRef)) ParticipatedRacesRef.Add(RaceLineRef);
}


void URacerManager::RemoveParticipatedRace(URaceLine_Base* RaceLineRef)
{
	if (ParticipatedRacesRef.Contains(RaceLineRef))
	{
		RaceLineRef->OnRaceSimulatedDelegate.RemoveAll(this);
		ParticipatedRacesRef.Remove(RaceLineRef);
	}
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
		NewStats.TeamName = Data.GetRacerTeamName();
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
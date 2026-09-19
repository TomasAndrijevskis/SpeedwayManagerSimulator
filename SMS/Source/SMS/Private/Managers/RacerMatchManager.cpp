
#include "Managers/RacerMatchManager.h"
#include "Subsystems/MatchManagerSubsystem.h"
#include "Subsystems/OverallRacerStatsSubsystem.h"
#include "UI/League/Program/Race/League_RaceLine_Base.h"


void URacerMatchManager::Initialize(const FRacerData& RacerData)
{
	Data.RacerData = RacerData;
	UE_LOG(LogTemp, Display, TEXT("Initialize %s"), *Data.GetRacerName());
}


void URacerMatchManager::CalculateRating(float GateModifier, float DistanceModifier, ETrackTypes TrackType)
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

	
	CurrentRacerRating = RacerRating * .2 + Start *.3 + DrivingSkill * .5;
	UE_LOG(LogTemp, Display, TEXT("Final Race rating: %f"), CurrentRacerRating);
}


void URacerMatchManager::AddParticipatedRace(int32 RaceID, int32 RaceLineID)
{
	if (!ParticipatedRaces.Contains(RaceID)) ParticipatedRaces.Add(RaceID, RaceLineID);
}


void URacerMatchManager::RemoveParticipatedRace(int32 RaceID)
{
	if (ParticipatedRaces.Contains(RaceID)) ParticipatedRaces.Remove(RaceID);
}


void URacerMatchManager::AddPoints(const ERaceResults NewResult, bool AddBonus)
{
	RacerPoints.Add(NewResult);
	if (AddBonus) RacerBonuses++;
	OnPointsAddedDelegate.Broadcast(NewResult, AddBonus);
}


int32 URacerMatchManager::CountOverallPoints()
{
	int32 sum = 0;
	if (UMatchManagerSubsystem* MatchManagerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMatchManagerSubsystem>())
	{
		if (UCompetitionRules* Rules = MatchManagerSubsystem->GetCompetitionRules())
		{
			for (const auto& Point : RacerPoints)
			{
				int32 Number = Rules->GetRaceResultAsNumber(Point);
				sum += Number;
			}
		}
	}
	return sum;
}


int32 URacerMatchManager::GetAmountOfWins() const
{
	int32 Amount = 0;
	for (const auto& Point : RacerPoints)
	{
		if (Point == ERaceResults::First) Amount++;
	}
	return Amount;
}

int32 URacerMatchManager::GetAmountOfUnfinishedRaces() const
{
	int32 Amount = 0;
	for (const auto& Point : RacerPoints)
	{
		if (Point == ERaceResults::Defect) Amount++;
	}
	return Amount;
}


void URacerMatchManager::CollectMatchStatistics()
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

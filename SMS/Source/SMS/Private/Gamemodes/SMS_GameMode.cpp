
#include "Gamemodes/SMS_GameMode.h"
#include "Data/RacersData/RacersDataAsset.h"


void ASMS_GameMode::BeginPlay()
{
	Super::BeginPlay();
	InitializeRacers();
	PrintTeams();
}


void ASMS_GameMode::InitializeRacers()
{
	for (const auto& RacerData : RacersDataAsset->Racers)
	{
		FString Name = RacerData.Name;
		ETeams Team = RacerData.InitialTeam;
		Racers.Add(Name, RacerData);
		Teams.FindOrAdd(Team).Add(Name);
	}
}


void ASMS_GameMode::PrintTeams()
{
	for (const auto& Team : Teams)
	{
		FString TeamName = StaticEnum<ETeams>()->GetNameStringByValue(Team.Key);
		UE_LOG(LogTemp, Error, TEXT("%s:"), *TeamName);
		for (const auto& RacerId : Team.Value)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s"),*RacerId);
		}
	}
}

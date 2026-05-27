
#include "Gamemodes/SMS_GameMode.h"
#include "Data/RacersData/RacersDataAsset.h"
#include "Gamemodes/Managers/MatchManager.h"


void ASMS_GameMode::BeginPlay()
{
	Super::BeginPlay();
	MatchManager = NewObject<UMatchManager>(this);
	if (!MatchManager) return;
	InitializeRacers();
}


void ASMS_GameMode::InitializeRacers()
{
	for (const auto& RacerData : RacersDataAsset->Racers)
	{
		FTeamRosterData Data;
		FString Name = RacerData.Name;
		ETeams Team = RacerData.InitialTeam;
		Data.Racers.Add(Name);
		Data.TeamID = Team;
		Racers.Add(Name, RacerData);
		Teams.FindOrAdd(Team).Racers.Add(Name);
		Teams.FindOrAdd(Team).TeamID = Team;
	}
	PrintTeams();
}


void ASMS_GameMode::PrintTeams()
{
	for (const auto& Team : Teams)
	{
		FText TeamName = StaticEnum<ETeams>()->GetDisplayNameTextByValue(Team.Key);
		UE_LOG(LogTemp, Error, TEXT("%s:"), *TeamName.ToString());
		
		for (const auto& Racer : Team.Value.Racers)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s - %i"),*Racer, Racers[Racer].RacerStats.Rating);
		}
	}
}


FTeamRosterData* ASMS_GameMode::GetTeamData(ETeams Team){return &Teams[Team];}
FTeamRosterData* ASMS_GameMode::GetTeamData(int TeamID){return &Teams[static_cast<ETeams>(TeamID)];}
int ASMS_GameMode::GetTeamsAmount()const{return Teams.Num()-1;}


#include "Gamemodes/SMS_GameMode.h"
#include "Data/RacersData/RacersDataAsset.h"
#include "Gamemodes/Managers/MatchManager.h"


void ASMS_GameMode::BeginPlay()
{
	Super::BeginPlay();
	MatchManager = NewObject<UMatchManager>(this);
	if (!MatchManager) return;
	MatchManager->Init();
	InitializeRacers();
}


void ASMS_GameMode::InitializeRacers()
{
	for (const auto& RacerData : RacersDataAsset->Racers)
	{
		FString RacerName = RacerData.Name;
		ETeams TeamID = RacerData.InitialTeam;
		FText TeamName = StaticEnum<ETeams>()->GetDisplayNameTextByValue(TeamID);
		Racers.Add(RacerName, RacerData);
		Teams.FindOrAdd(TeamID).Racers.Add(RacerName);
		Teams.FindOrAdd(TeamID).TeamID = TeamID;
		Teams.FindOrAdd(TeamID).TeamName = TeamName;
	}
	//PrintTeams();
}


void ASMS_GameMode::PrintTeams()
{
	for (const auto& Team : Teams)
	{
		UE_LOG(LogTemp, Error, TEXT("%s:"), *Team.Value.TeamName.ToString());
		
		for (const auto& Racer : Team.Value.Racers)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s - %i"),*Racer, Racers[Racer].RacerStats.Rating);
		}
	}
}


FText* ASMS_GameMode::GetTeamName(int TeamID){return &Teams[static_cast<ETeams>(TeamID)].TeamName;}
FText* ASMS_GameMode::GetTeamName(ETeams Team){return &Teams[Team].TeamName;}
FTeamRosterData* ASMS_GameMode::GetTeamData(ETeams Team){return &Teams[Team];}
FTeamRosterData* ASMS_GameMode::GetTeamData(int TeamID){return &Teams[static_cast<ETeams>(TeamID)];}
int ASMS_GameMode::GetTeamsAmount()const{return Teams.Num()-1;}

#include "Gamemodes/SMS_GameMode.h"
#include "Data/RacersData/RacersDataAsset.h"
#include "Managers/MatchManager.h"


void ASMS_GameMode::BeginPlay()
{
	Super::BeginPlay();
	InitializeManagers();
	InitializeRacers();
}


void ASMS_GameMode::InitializeManagers()
{
	MatchManager = NewObject<UMatchManager>(this);
	if (!MatchManager) return;
	MatchManager->Init(this);
}


void ASMS_GameMode::InitializeRacers()
{
	for (const auto& RacerData : RacersDataAsset->Racers)
	{
		FRacerData Racer;
		Racer.ID = RacerData.ID;
		Racer.Name = RacerData.Name;
		Racer.RacerStats = RacerData.RacerStats;
		ETeams TeamID = RacerData.InitialTeam;
		FText TeamName = StaticEnum<ETeams>()->GetDisplayNameTextByValue(TeamID);
		Teams.FindOrAdd(TeamID).TeamID = TeamID;
		Teams.FindOrAdd(TeamID).TeamName = TeamName;
		Teams.FindOrAdd(TeamID).Racers.Add(Racer);
	}
	PrintTeams();
}


void ASMS_GameMode::PrintTeams()
{
	for (const auto& Team : Teams)
	{
		UE_LOG(LogTemp, Error, TEXT("%s:"), *Team.Value.TeamName.ToString());
		
		for (const auto& Racer : Team.Value.Racers)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s - %i"), *Racer.Name, Racer.RacerStats.Rating);
		}
	}
}


const FText& ASMS_GameMode::GetTeamName(int TeamID)const{return Teams.FindChecked(static_cast<ETeams>(TeamID)).TeamName;}
const FText& ASMS_GameMode::GetTeamName(ETeams Team)const{return Teams.FindChecked(Team).TeamName;}
FTeamRosterData* ASMS_GameMode::GetTeamData(ETeams Team){return &Teams.FindChecked(Team);}
FTeamRosterData* ASMS_GameMode::GetTeamData(int TeamID){return &Teams.FindChecked(static_cast<ETeams>(TeamID));}
int ASMS_GameMode::GetTeamsAmount()const{return Teams.Num()-1;}
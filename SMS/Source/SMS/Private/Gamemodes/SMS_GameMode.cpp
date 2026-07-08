
#include "Gamemodes/SMS_GameMode.h"
#include "Data/RacersData/RacersDataAsset.h"
#include "Managers/MatchManager.h"
#include "Managers/ScoreManager.h"


void ASMS_GameMode::BeginPlay()
{
	Super::BeginPlay();
	InitializeRacers();
}


void ASMS_GameMode::CreateRequiredManagers()
{
	CurrentMatchManager = NewObject<UMatchManager>(this);
	CurrentScoreManager = NewObject<UScoreManager>(this);
	if (!CurrentMatchManager || !CurrentScoreManager) return;
	CurrentMatchManager->InitializeManager(this);
}


void ASMS_GameMode::DestroyUsedManagers()
{
	CurrentMatchManager = nullptr;
}


void ASMS_GameMode::InitializeRacers()
{
	for (auto& Racer : RacersDataAsset->Racers)
	{
		FRacerData RacerData;
		RacerData = Racer;
		ETeams TeamID = Racer.InitialTeam;
		FText TeamName = StaticEnum<ETeams>()->GetDisplayNameTextByValue(TeamID);
		Teams.FindOrAdd(TeamID).TeamID = TeamID;
		Teams.FindOrAdd(TeamID).TeamName = TeamName;
		Teams.FindOrAdd(TeamID).Racers.Add(RacerData);
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
			UE_LOG(LogTemp, Warning, TEXT("%s - %i"), *Racer.Name, Racer.RacerStats.Rating);
		}
	}
}


const FText& ASMS_GameMode::GetTeamName(int TeamID)const{return Teams.FindChecked(static_cast<ETeams>(TeamID)).TeamName;}
FTeamMatchData ASMS_GameMode::GetTeamData(int TeamID){return Teams.FindChecked(static_cast<ETeams>(TeamID));}
int ASMS_GameMode::GetTeamsAmount()const{return Teams.Num();}
UMatchManager* ASMS_GameMode::GetMatchManager() const{return CurrentMatchManager;}
UScoreManager* ASMS_GameMode::GetScoreManager() const{return CurrentScoreManager;}

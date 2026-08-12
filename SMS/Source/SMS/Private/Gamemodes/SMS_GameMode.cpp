
#include "Gamemodes/SMS_GameMode.h"
#include "Managers/MatchManager.h"
#include "Subsystems/RulesSubsystem.h"
#include "Subsystems/StandingsSubsystem.h"


void ASMS_GameMode::BeginPlay()
{
	Super::BeginPlay();
	if (URulesSubsystem* Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<URulesSubsystem>())
	{
		Subsystem->InitializeRules();
	}
	InitializeRacers();
}


void ASMS_GameMode::CreateRequiredManagers()
{
	CurrentMatchManager = NewObject<UMatchManager>(this);
	if (!CurrentMatchManager) return;
	CurrentMatchManager->InitializeManager(this);
}


void ASMS_GameMode::DestroyUsedManagers()
{
	CurrentMatchManager = nullptr;
}


void ASMS_GameMode::InitializeRacers()
{
	if (!RacersDataTable) return;
	TArray<FRacerData*> Racers;
	RacersDataTable->GetAllRows(TEXT("Find racers"), Racers);
	for (const auto& Racer : Racers)
	{
		FRacerData RacerData = *Racer;
		ETeams TeamID = Racer->InitialTeam;
		FString TeamName = StaticEnum<ETeams>()->GetDisplayNameTextByIndex(TeamID).ToString();
		Teams.FindOrAdd(TeamID).TeamID = TeamID;
		Teams.FindOrAdd(TeamID).TeamName = TeamName;
		Teams.FindOrAdd(TeamID).Racers.Add(RacerData);
	}
	//PrintTeams();
	InitializeTeamsStatistics();
}


void ASMS_GameMode::InitializeTeamsStatistics()
{
	if (UStandingsSubsystem* Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UStandingsSubsystem>())
	{
		for (const auto& Team : Teams)
		{
			FTeamStatistics NewTeamStatistics;
			NewTeamStatistics.TeamID = Team.Value.TeamID;
			NewTeamStatistics.TeamName = Team.Value.TeamName;
			Subsystem->AddTeamStatistics(NewTeamStatistics);
		}
	}
}


void ASMS_GameMode::PrintTeams()
{
	for (const auto& Team : Teams)
	{
		UE_LOG(LogTemp, Error, TEXT("%s:"), *Team.Value.TeamName);
		
		for (const auto& Racer : Team.Value.Racers)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s - %i"), *Racer.Name, Racer.RacerStats.Rating);
		}
	}
}


const FString& ASMS_GameMode::GetTeamName(int32 TeamID)const{return Teams.FindChecked(static_cast<ETeams>(TeamID)).TeamName;}
FTeamMatchData& ASMS_GameMode::GetTeamData(int32 TeamID){return Teams.FindChecked(static_cast<ETeams>(TeamID));}
int32 ASMS_GameMode::GetTeamsAmount()const{return Teams.Num();}
UMatchManager* ASMS_GameMode::GetMatchManager() const{return CurrentMatchManager;}
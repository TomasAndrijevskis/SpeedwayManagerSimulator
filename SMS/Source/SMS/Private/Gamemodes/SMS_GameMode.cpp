
#include "Gamemodes/SMS_GameMode.h"
#include "Data/Locations/LocationsDataAsset.h"
#include "Data/Track/TrackDataAsset.h"
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
	InitializeTeamsStatistics();
	SetTrackData();
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
		ETeams Team = Racer->InitialTeam;
		FString TeamName = StaticEnum<ETeams>()->GetDisplayNameTextByValue(static_cast<int32>(Team)).ToString();
		Teams.FindOrAdd(Team).Team = Team;
		Teams.FindOrAdd(Team).TeamName = TeamName;
		Teams.FindOrAdd(Team).Racers.Add(RacerData);
	}
	//PrintTeams();
}


void ASMS_GameMode::SetTrackData()
{
	for (const auto& Location : LocationsDataAsset->Locations)
	{
		for (const auto& City : Location.Value.City)
		{
			if (City.Value.HasTeam)
			{
				FString CityName = UEnum::GetDisplayValueAsText(City.Key).ToString();
				UE_LOG(LogTemp, Warning, TEXT("%s"), *CityName)
				Teams.FindOrAdd(City.Value.Team).TrackData = City.Value.TrackData->TrackData;
			}
		}
	}
}


void ASMS_GameMode::InitializeTeamsStatistics()
{
	if (UStandingsSubsystem* Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UStandingsSubsystem>())
	{
		for (const auto& Team : Teams)
		{
			FTeamStatistics NewTeamStatistics;
			NewTeamStatistics.Team = Team.Value.Team;
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


const FString& ASMS_GameMode::GetTeamName(ETeams Team)const{return Teams.FindChecked(Team).TeamName;}
FTeamMatchData& ASMS_GameMode::GetTeamData(ETeams Team){return Teams.FindChecked(Team);}
int32 ASMS_GameMode::GetTeamsAmount()const{return Teams.Num();}
UMatchManager* ASMS_GameMode::GetMatchManager() const{return CurrentMatchManager;}
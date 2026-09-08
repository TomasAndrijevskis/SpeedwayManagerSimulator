
#include "Gamemodes/SMS_GameMode.h"
#include "Data/Locations/LocationsDataAsset.h"
#include "Data/Track/TrackDataAsset.h"
#include "Managers/RacerCareerManager.h"
#include "Subsystems/RulesSubsystem.h"
#include "Subsystems/StandingsSubsystem.h"


void ASMS_GameMode::BeginPlay()
{
	Super::BeginPlay();
	if (URulesSubsystem* Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<URulesSubsystem>())
	{
		Subsystem->InitializeRules();
	}
	InitializeTeams();
	InitializeTeamsStatistics();
	SetTrackData();
}


void ASMS_GameMode::InitializeTeams()
{
	if (!RacersDataTable) return;
	TArray<FRacerData*> Racers;
	RacersDataTable->GetAllRows(TEXT("Find racers"), Racers);
	for (const auto& Racer : Racers)
	{
		URacerCareerManager* InitializedRacer = InitializeRacer(*Racer);
		ETeams Team = Racer->InitialTeam;
		FString TeamName = StaticEnum<ETeams>()->GetDisplayNameTextByValue(static_cast<int32>(Team)).ToString();
		Teams.FindOrAdd(Team).Team = Team;
		Teams.FindOrAdd(Team).Racers.Add(InitializedRacer);
	}
	//PrintTeams();
}


URacerCareerManager* ASMS_GameMode::InitializeRacer(const FRacerData& RacerData)
{
	if (URacerCareerManager* RacerManager = NewObject<URacerCareerManager>(this))
	{
		RacerManager->Initialize(RacerData);
		return RacerManager;
	}
	return nullptr;
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
			Subsystem->AddTeamStatistics(NewTeamStatistics);
		}
	}
}
/*
TArray<TObjectPtr<URacerCareerManager>> ASMS_GameMode::GetTopRacers() const
{
	TArray<TObjectPtr<URacerCareerManager>> Racers;
	TArray<TObjectPtr<URacerCareerManager>> tempRacers;
	for (const auto& Team : Teams)
	{
		for (const auto& Racer : Team.Value.Racers)
		{
			tempRacers.Add(Racer);
		}
	}
	tempRacers.Sort([](const FRacerData& L1, const FRacerData& L2)
	{
		return L1.RacerStats.Rating > L2.RacerStats.Rating;
	});

	for (int i = 0; i < 16; i++)
	{
		Racers.Add(tempRacers[i]);
	}*/
	/*for (const auto& Racer : Racers)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s - %i"), *Racer, Racer.RacerStats.Rating);
	}
	return Racers;
}
*/

void ASMS_GameMode::PrintTeams()
{
	for (const auto& Team : Teams)
	{
		/*for (const auto& Racer : Team.Value.Racers)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s - %i"), *Racer.Name, Racer.RacerStats.Rating);
		}*/
	}
}


FTeamData& ASMS_GameMode::GetTeamData(ETeams Team){return Teams.FindChecked(Team);}
FString ASMS_GameMode::GetTeamName(ETeams Team) const{return Teams.FindChecked(Team).GetTeamName();}
int32 ASMS_GameMode::GetTeamsAmount()const{return Teams.Num();}

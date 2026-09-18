
#include "Gamemodes/SMS_GameMode.h"
#include "Data/Locations/LocationsDataAsset.h"
#include "Data/Track/TrackDataAsset.h"
#include "Managers/RacerCareerManager.h"
#include "Subsystems/StandingsSubsystem.h"


void ASMS_GameMode::BeginPlay()
{
	Super::BeginPlay();
	InitializeTeams();
	InitializeTeamsStatistics();
	SetTrackData();
	SetTopRacers();
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


FTrackData ASMS_GameMode::GetTrackData(ECities CityToFind) const
{
	for (const auto& Location : LocationsDataAsset->Locations)
	{
		for (const auto& City : Location.Value.City)
		{
			if (City.Key == CityToFind)
			{
				return City.Value.TrackData->TrackData;
			}
		}
	}
	return FTrackData{};
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

void ASMS_GameMode::SetTopRacers()
{
	for (const auto& Team : Teams)
	{
		for (const auto& Racer : Team.Value.Racers)
		{
			TopRacers.Add(Racer);
		}
	}
	TopRacers.Sort([](URacerCareerManager& L1, URacerCareerManager& L2)
	{
		return L1.GetRacerData().RacerStats.Rating > L2.GetRacerData().RacerStats.Rating;
	});

	while (TopRacers.Num() != 16)
	{
		TopRacers.RemoveSingle(TopRacers.Last());
	}
	UE_LOG(LogTemp,Error, TEXT("top racers:"))
	for (const auto& Racer : TopRacers)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s - %i"), *Racer->GetRacerData().Name, Racer->GetRacerData().RacerStats.Rating);
	}
}


void ASMS_GameMode::PrintTeams()
{
	/*for (const auto& Team : Teams)
	{
		for (const auto& Racer : Team.Value.Racers)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s - %i"), *Racer.Name, Racer.RacerStats.Rating);
		}
	}*/
}
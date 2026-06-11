
#include "Managers/TeamRostersManager.h"


void UTeamRostersManager::AddRacer(FString Name, int RaceStatsLineID)
{
	//UE_LOG(LogTemp, Warning, TEXT("ID: %i, Name: %s"), Id, *Name);
	Racers.Add(RaceStatsLineID, TeamRosterData.Racers.Find(Name));
}


void UTeamRostersManager::ForEachRacer(TFunction<void(const FString&, int)> Callback)
{
	for (const auto& Racer : Racers)
	{
		Callback(Racer.Value->Name, Racer.Key);
	}
}


void UTeamRostersManager::SetTeamData(const FTeamRosterData& Data)
{
	TeamRosterData = Data;
}

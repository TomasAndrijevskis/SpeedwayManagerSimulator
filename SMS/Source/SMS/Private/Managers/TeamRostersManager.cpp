
#include "Managers/TeamRostersManager.h"


void UTeamRostersManager::AddRacer(FString Name, int Id)
{
	//UE_LOG(LogTemp, Warning, TEXT("ID: %i, Name: %s"), Id, *Name);
	Racers.Add(Id, Name);
}


void UTeamRostersManager::ForEachRacer(TFunction<void(const FString&, int)> Callback)
{
	for (const auto& Racer : Racers)
	{
		Callback(Racer.Value, Racer.Key);
	}
}
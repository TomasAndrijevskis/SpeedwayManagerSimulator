
#include "Managers/TeamManager.h"
#include "Gamemodes/SMS_GameMode.h"
#include "Kismet/GameplayStatics.h"


void UTeamManager::AddRacersToLineup(const FString& RacerName, int RacerStatLineID)
{
	if (const auto* FoundRacerData = Algo::FindByPredicate(TeamRosterData->Racers, [&RacerName](const auto& RacerData)
	{
		return RacerData.Name == RacerName;
	}))
	{
		Racers.Add(RacerStatLineID, *FoundRacerData);
	}
}


void UTeamManager::ForEachRacer(TFunction<void(const FString&, int)> Callback)
{
	for (const auto& Racer : Racers)
	{
		Callback(Racer.Value.Name, Racer.Key);
	}
}

void UTeamManager::ForEachRacer(TFunction<void(const FString&)> Callback)
{
	for (const auto& Racer : TeamRosterData->Racers)
	{
		Callback(Racer.Name);
	}
}


void UTeamManager::SetTeamData(int ID)
{
	ASMS_GameMode* GameMode = Cast<ASMS_GameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	TeamRosterData = GameMode->GetTeamData(ID);
}


const FString& UTeamManager::GetTeamName() const
{
	return TeamRosterData->TeamName.ToString();
}
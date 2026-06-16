
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


void UTeamManager::ForEachRacerInLineup(TFunction<void(int, const FRacerData&)> Callback)
{
	for (const auto& Racer : Racers)
	{
		Callback(Racer.Key, Racer.Value);
	}
}


void UTeamManager::ForEachRacerInRoster(TFunction<void(const FRacerData&)> Callback)
{
	for (const auto& Racer : TeamRosterData->Racers)
	{
		Callback(Racer);
	}
}


void UTeamManager::SetTeamData(int ID)
{
	ASMS_GameMode* GameMode = Cast<ASMS_GameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	TeamRosterData = GameMode->GetTeamData(ID);

	/*UE_LOG(LogTemp, Error, TEXT("%s:"), *GetTeamName());
	for (const auto& Racer : TeamRosterData->Racers)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s - %i"), *Racer.Name, Racer.RacerStats.Rating);
	}*/
}


const FString& UTeamManager::GetTeamName() const
{
	return TeamRosterData->TeamName.ToString();
}
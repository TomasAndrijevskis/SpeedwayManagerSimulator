
#include "Managers/TeamManager.h"
#include "Gamemodes/SMS_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/RacerManager.h"
#include "UI/League/Program/RacerStatsLine.h"


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


void UTeamManager::CreateRacerManagers()
{
	for (auto& Racer : Racers)
	{
		URacerManager* NewRacerManager = NewObject<URacerManager>(this);
		if (NewRacerManager)
		{
			NewRacerManager->Initialize(Racer.Key, Racer.Value);
			Racer.Value.RacerManager = NewRacerManager;
		}
	}
}


void UTeamManager::SetTeamData(int ID)
{
	ASMS_GameMode* GameMode = Cast<ASMS_GameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	TeamRosterData = GameMode->GetTeamData(ID);
}


void UTeamManager::RandomizeTeamRoster()
{
	for (const auto& RacerStatsLine : RacerStatsLines)
	{
		RacerStatsLine->ChooseRandomOption();
	}
}


void UTeamManager::FillTeamRosterOptions()
{
	for (const auto& RacerStatsLine : RacerStatsLines)
	{
		ForEachRacerInRoster([this, RacerStatsLine](const FRacerData& Data)
		{
			RacerStatsLine->AddOption(Data.Name);
		});
	}
}


void UTeamManager::AddRacerStatsLine(URacerStatsLine* RacerStatsLine){RacerStatsLines.Add(RacerStatsLine);}
TArray<URacerStatsLine*>& UTeamManager::GetRacerStatsLines(){return RacerStatsLines;}
const FString& UTeamManager::GetTeamName() const{return TeamRosterData->TeamName.ToString();}

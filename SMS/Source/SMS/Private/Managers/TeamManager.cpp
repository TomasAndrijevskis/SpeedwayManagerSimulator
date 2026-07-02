
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
		FRacerMatchData NewRacerData;
		NewRacerData.RacerData = *FoundRacerData;
		NewRacerData.RacerNumber = RacerStatLineID;
		Racers.Add(RacerStatLineID, NewRacerData);
	}
}


void UTeamManager::ForEachRacerInLineup(TFunction<void(int)> Callback)
{
	ForEachRacerInLineup([&Callback](const FRacerMatchData& Data)
	{
		Callback(Data.RacerNumber);
	});
}


void UTeamManager::ForEachRacerInLineup(TFunction<void(const FRacerMatchData&)> Callback)
{
	for (const auto& Racer : Racers)
	{
		Callback(Racer.Value);
	}
}


void UTeamManager::ForEachRacerInLineup(TFunction<void(const FRacerMatchData&, URacerManager*)> Callback)
{
	for (const auto& Racer : Racers)
	{
		if (URacerManager** FoundManager = RacerManagers.Find(Racer.Key))
		{
			Callback(Racer.Value, *FoundManager);
		}
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
	for (const auto& Racer : Racers)
	{
		URacerManager* NewRacerManager = NewObject<URacerManager>(this);
		if (NewRacerManager)
		{
			NewRacerManager->Initialize(Racer.Value);
			RacerManagers.Add(Racer.Key, NewRacerManager);
		}
	}
}


void UTeamManager::SetTeamData(int ID, bool IsVisitor)
{
	ASMS_GameMode* GameMode = Cast<ASMS_GameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	TeamRosterData = GameMode->GetTeamData(ID);
	bIsVisitorTeam = IsVisitor;
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
bool UTeamManager::IsVisitorTeam()const{return bIsVisitorTeam;}
TMap<int, URacerManager*> UTeamManager::GetRacerManagers() {return RacerManagers;}
const FString& UTeamManager::GetTeamName() const{return TeamRosterData->TeamName.ToString();}

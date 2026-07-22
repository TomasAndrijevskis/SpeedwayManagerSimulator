
#include "Managers/TeamManager.h"
#include "Managers/RacerManager.h"
#include "UI/League/Program/RacerStatsLine.h"


void UTeamManager::AddRacersToLineup(const FString& RacerName, int RacerStatLineID)
{
	if (const auto* FoundRacerData = Algo::FindByPredicate(TeamData->Racers, [&RacerName](const auto& RacerData)
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


void UTeamManager::ForEachRacerInLineup(TFunction<void(URacerManager*)> Callback)
{
	for (const auto& Racer : Racers)
	{
		if (URacerManager** FoundManager = RacerManagers.Find(Racer.Key))
		{
			Callback(*FoundManager);
		}
	}
}


void UTeamManager::GetAvailableReplacementRacers(bool IsTeamLosing, const URacerManager* RacerManagerRef, TFunction<void(URacerManager*)> Callback)
{
	ForEachRacerInLineup([&Callback, IsTeamLosing, RacerManagerRef](URacerManager* RacerManager)
	{
		if (IsTeamLosing)
		{
			if (RacerManager->CanDriveMore() && RacerManager != RacerManagerRef)
				Callback(RacerManager);
		}
		else
		{
			if (RacerManager->CanDriveMore()
				&& (RacerManager->IsJunior() || RacerManager->IsReplacement())
				&& RacerManager != RacerManagerRef)
				Callback(RacerManager);
		}
	});
}


void UTeamManager::GetAvailableRacers(const URacerManager* RacerManagerRef,TFunction<void(URacerManager*)> Callback)
{
	ForEachRacerInLineup([&Callback, RacerManagerRef](URacerManager* RacerManager)
	{
		if (RacerManager->CanDriveMore() && RacerManager != RacerManagerRef && !RacerManager->ParticipatedInNominatedRace())
			Callback(RacerManager);
	});
}


void UTeamManager::ForEachRacerInRoster(TFunction<void(const FRacerData&)> Callback)
{
	for (const auto& Racer : TeamData->Racers)
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


void UTeamManager::RandomizeTeamRoster()
{
	for (const auto& RacerStatsLine : RacerStatsLines)
	{
		RacerStatsLine->ChooseRandomOption(ChosenOptions);
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


void UTeamManager::LockChosenRacers() const
{
	for (const auto& StatsLine : RacerStatsLines)
	{
		StatsLine->LockRacer();
	}
}


bool UTeamManager::CheckChosenRacers() const
{
	if (Racers.Num() < 6) return false;
	return true;
}


void UTeamManager::SetTeamData(FTeamMatchData* NewTeamData){TeamData = NewTeamData;}
void UTeamManager::AddRacerStatsLine(URacerStatsLine* RacerStatsLine){RacerStatsLines.Add(RacerStatsLine);}
TArray<URacerStatsLine*>& UTeamManager::GetRacerStatsLines(){return RacerStatsLines;}
bool UTeamManager::IsVisitorTeam()const{return TeamData->IsVisitorTeam;}
TMap<int, URacerManager*> UTeamManager::GetRacerManagers() {return RacerManagers;}
const FString& UTeamManager::GetTeamName() const{return TeamData->TeamName.ToString();}
int UTeamManager::GetTeamID() const{return TeamData->TeamID;}

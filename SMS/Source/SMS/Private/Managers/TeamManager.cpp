
#include "Managers/TeamManager.h"
#include "Managers/RacerManager.h"
#include "Managers/RuleBook.h"
#include "UI/League/Program/RacerStatsLine.h"


void UTeamManager::AddRacersToLineup(const FString& RacerName, int32 RacerStatLineID)
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


void UTeamManager::ForEachRacerInLineup(TFunction<void(int32)> Callback)
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


void UTeamManager::GetAvailableReplacementRacers(const URacerManager* OriginalRacerManager, TFunction<void(URacerManager*)> Callback)
{
	ForEachRacerInLineup([&Callback, OriginalRacerManager, this](URacerManager* ReplacementRacerManager)
	{
		if (RuleBook->CanReplace(OriginalRacerManager, ReplacementRacerManager))
		{
			Callback(ReplacementRacerManager);
		}
	});
}


void UTeamManager::GetAvailableRacers(TFunction<void(URacerManager*)> Callback)
{
	ForEachRacerInLineup([&Callback, this](URacerManager* RacerManager)
	{
		if (RuleBook->CanParticipateInNominatedRace(RacerManager))
		{
			Callback(RacerManager);
		}
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


void UTeamManager::MakeRandomTeamRoster()
{
	int32 Amount = RacerStatsLines.Num();
	if (Amount == 0) return;
	for (int32 i = Amount - 1; i >= 0; i--)
	{
		RacerStatsLines[i]->ChooseRandomOption();
	}
}


void UTeamManager::FillTeamRosterOptions()
{
	if (!RuleBook) return;
	for (auto& RacerStatsLine : RacerStatsLines)
	{
		ForEachRacerInRoster([this, RacerStatsLine](const FRacerData& Data)
		{
			if (RuleBook->IsRacerEligible(RacerStatsLine, Data.Age))
			RacerStatsLine->AddOption(Data);
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


void UTeamManager::UpdateStatsLineOptions(const URacerStatsLine* RacerStatsLineRef, const FString& SelectedOption, FRacerData& PreviousOptionData)
{
	for (auto& StatsLine : RacerStatsLines)
	{
		if (StatsLine != RacerStatsLineRef)
		{
			StatsLine->RemoveOption(SelectedOption);
			if (PreviousOptionData.Name != "")
			{
				if (RuleBook->IsRacerEligible(StatsLine, PreviousOptionData.Age)) StatsLine->AddOption(PreviousOptionData);
			}
		}
		if (StatsLine->GetNumberOfOptions() == 1) StatsLine->AddOption(FRacerData());
	}
}


bool UTeamManager::IsRosterValid() const
{
	if (Racers.Num() < 6) return false;
	return true;
}


void UTeamManager::SetTeamData(FTeamMatchData* NewTeamData){TeamData = NewTeamData;}
void UTeamManager::SetRuleBook(URuleBook* NewRuleBook){RuleBook = NewRuleBook;}
void UTeamManager::AddRacerStatsLine(URacerStatsLine* RacerStatsLine){RacerStatsLines.Add(RacerStatsLine);}
TArray<URacerStatsLine*>& UTeamManager::GetRacerStatsLines(){return RacerStatsLines;}
bool UTeamManager::IsVisitorTeam()const{return TeamData->IsVisitorTeam;}
TMap<int32, URacerManager*> UTeamManager::GetRacerManagers() {return RacerManagers;}
const FString& UTeamManager::GetTeamName() const{return TeamData->TeamName.ToString();}
int32 UTeamManager::GetTeamID() const{return TeamData->TeamID;}

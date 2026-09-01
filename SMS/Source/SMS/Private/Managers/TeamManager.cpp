
#include "Managers/TeamManager.h"
#include "Managers/RacerManager.h"
#include "Managers/ScoreManager.h"
#include "Subsystems/RulesSubsystem.h"
#include "Subsystems/StandingsSubsystem.h"
#include "UI/League/Program/League_RacerStatsLine.h"


void UTeamManager::InitializeManager()
{
	RulesSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<URulesSubsystem>();
}


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
	if (!RulesSubsystem || !ScoreManager) return;
	int32 OwnTeamScore = ScoreManager->GetTeamScore(OriginalRacerManager->IsVisitor());
	int32 EnemyTeamScore = ScoreManager->GetTeamScore(!OriginalRacerManager->IsVisitor());
	ForEachRacerInLineup([&Callback, OriginalRacerManager, this, OwnTeamScore, EnemyTeamScore](URacerManager* ReplacementRacerManager)
	{
		if (RulesSubsystem->CanReplace(OriginalRacerManager, ReplacementRacerManager, OwnTeamScore, EnemyTeamScore))
		{
			Callback(ReplacementRacerManager);
		}
	});
}


void UTeamManager::GetAvailableRacers(TFunction<void(URacerManager*)> Callback)
{
	if (!RulesSubsystem) return;
	ForEachRacerInLineup([&Callback, this](URacerManager* RacerManager)
	{
		if (RulesSubsystem->CanParticipateInNominatedRace(RacerManager))
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
	if (!RulesSubsystem) return;
	for (auto& RacerStatsLine : RacerStatsLines)
	{
		ForEachRacerInRoster([this, RacerStatsLine](const FRacerData& Data)
		{
			if (RulesSubsystem->IsRacerEligible(RacerStatsLine->GetID(), Data.Age))
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


void UTeamManager::UpdateStatsLineOptions(const ULeague_RacerStatsLine* RacerStatsLineRef, const FString& SelectedOption, FRacerData& PreviousOptionData)
{
	if (!RulesSubsystem) return;
	for (auto& RacerStatsLine : RacerStatsLines)
	{
		if (RacerStatsLine != RacerStatsLineRef)
		{
			RacerStatsLine->RemoveOption(SelectedOption);
			if (PreviousOptionData.Name != "")
			{
				if (RulesSubsystem->IsRacerEligible(RacerStatsLine->GetID(), PreviousOptionData.Age)) RacerStatsLine->AddOption(PreviousOptionData);
			}
		}
		if (RacerStatsLine->GetNumberOfOptions() == 1) RacerStatsLine->AddOption(FRacerData());
	}
}


void UTeamManager::CollectTeamStatistics(const EMatchResults Result, const TMap<ETeams, int32>& OpponentResult)
{
	if (UStandingsSubsystem* Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UStandingsSubsystem>())
	{
		FTeamStatistics TeamStats;
		TeamStats.Team = GetTeam();
		FTeamMatchStatistics MatchStats;
		MatchStats.IsVisitorTeam = IsVisitorTeam();
		MatchStats.TeamScore = TeamData->TeamScore;
		MatchStats.Result = Result;
		MatchStats.OpponentResult = OpponentResult;
		
		TeamStats.MatchStatistics.Add(MatchStats);
		
		Subsystem->AddTeamStatistics(TeamStats);
	}
}



bool UTeamManager::IsRosterValid() const
{
	if (Racers.Num() < 6) return false;
	return true;
}


void UTeamManager::SetTeamData(FTeamMatchData* NewTeamData){TeamData = NewTeamData;}
void UTeamManager::SetScoreManager(UScoreManager* ScoreManagerRef){ScoreManager = ScoreManagerRef;}
void UTeamManager::AddRacerStatsLine(ULeague_RacerStatsLine* RacerStatsLine){RacerStatsLines.Add(RacerStatsLine);}
TArray<ULeague_RacerStatsLine*>& UTeamManager::GetRacerStatsLines(){return RacerStatsLines;}
bool UTeamManager::IsVisitorTeam()const{return TeamData->IsVisitorTeam;}
TMap<int32, URacerManager*>& UTeamManager::GetRacerManagers() {return RacerManagers;}
const FString& UTeamManager::GetTeamName() const{return TeamData->TeamName;}
ETeams UTeamManager::GetTeam() const{return TeamData->Team;}
int32 UTeamManager::GetTeamScore() const{return TeamData->TeamScore;}
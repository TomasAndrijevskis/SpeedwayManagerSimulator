
#include "Managers/TeamManager.h"
#include "Managers/RacerMatchManager.h"
#include "Rules/League_Rules.h"
#include "Subsystems/MatchManagerSubsystem.h"
#include "Subsystems/RulesSubsystem.h"
#include "Subsystems/StandingsSubsystem.h"
#include "UI/League/Program/League_RacerStatsLine.h"


void UTeamManager::InitializeManager()
{
	RulesSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<URulesSubsystem>();
}


void UTeamManager::AddRacersToLineup(const FString& RacerName, int32 RacerStatLineID)
{
	for (auto& RacerManger : TeamData.Racers)
	{
		if (RacerManger && RacerManger->GetRacerName() == RacerName)
		{
			RacerManger->SetRacerNumber(RacerStatLineID);
			Racers.Add(RacerStatLineID, RacerManger);
			break;
		}
	}
}


void UTeamManager::ForEachRacerInLineup(TFunction<void(int32)> Callback)
{
	ForEachRacerInLineup(TFunction<void(const TObjectPtr<URacerMatchManager>&)>([&Callback](const TObjectPtr<URacerMatchManager>& RacerManager)
	{
		Callback(RacerManager->GetRacerNumber());
	}));
}


void UTeamManager::ForEachRacerInLineup(TFunction<void(const TObjectPtr<URacerMatchManager>&)> Callback)
{
	for (const auto& Racer : Racers)
	{
		Callback(Racer.Value);
	}
}


void UTeamManager::GetAvailableReplacementRacers(const URacerMatchManager* OriginalRacerManager, TFunction<void(const TObjectPtr<URacerMatchManager>&)> Callback)
{
	if (!RulesSubsystem) return;
	if (UMatchManagerSubsystem* MatchManagerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMatchManagerSubsystem>())
	{
		if (ULeague_Rules* Rules = Cast<ULeague_Rules>(MatchManagerSubsystem->GetCompetitionRules()))
		{
			int32 OwnTeamScore = Rules->GetTeamScore(OriginalRacerManager->IsVisitor());
			int32 EnemyTeamScore = Rules->GetTeamScore(!OriginalRacerManager->IsVisitor());
			ForEachRacerInLineup(TFunction<void(const TObjectPtr<URacerMatchManager>&)>([&Callback, OriginalRacerManager, this, OwnTeamScore, EnemyTeamScore](URacerMatchManager* ReplacementRacerManager)
			{
				if (RulesSubsystem->CanReplace(OriginalRacerManager, ReplacementRacerManager, OwnTeamScore, EnemyTeamScore))
				{
					Callback(ReplacementRacerManager);
				}
			}));
		}
	}
}


void UTeamManager::GetAvailableRacers(TFunction<void(URacerMatchManager*)> Callback)
{
	if (!RulesSubsystem) return;
	ForEachRacerInLineup(TFunction<void(const TObjectPtr<URacerMatchManager>&)>([&Callback, this](URacerMatchManager* RacerManager)
	{
		if (RulesSubsystem->CanParticipateInNominatedRace(RacerManager))
		{
			Callback(RacerManager);
		}
	}));
}


void UTeamManager::ForEachRacerInRoster(TFunction<void(URacerMatchManager*)> Callback)
{
	for (const auto& Racer : TeamData.Racers)
	{
		Callback(Racer);
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
		ForEachRacerInRoster([this, RacerStatsLine](const TObjectPtr<URacerMatchManager>& RacerManager)
		{
			if (RulesSubsystem->IsRacerEligible(RacerStatsLine->GetID(), RacerManager->GetRacerAge()))
			RacerStatsLine->AddOption(RacerManager);
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


void UTeamManager::UpdateStatsLineOptions(const ULeague_RacerStatsLine* RacerStatsLineRef, const FString& SelectedOption, const TObjectPtr<URacerMatchManager>& PreviousOptionData)
{
	if (!RulesSubsystem) return;
	for (auto& RacerStatsLine : RacerStatsLines)
	{
		if (RacerStatsLine != RacerStatsLineRef)
		{
			RacerStatsLine->RemoveOption(SelectedOption);
			if (PreviousOptionData && PreviousOptionData->GetRacerName() != "")
			{
				if (RulesSubsystem->IsRacerEligible(RacerStatsLine->GetID(), PreviousOptionData->GetRacerAge())) RacerStatsLine->AddOption(PreviousOptionData);
			}
		}
		if (RacerStatsLine->GetNumberOfOptions() == 1) RacerStatsLine->AddOption(nullptr);
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
		MatchStats.TeamScore = TeamData.TeamScore;
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


void UTeamManager::UpdateScore(int32 PointsToAdd, int32 RaceID)
{
	TeamData.TeamScore += PointsToAdd;
	TeamData.EachRaceScore.FindOrAdd(RaceID) += PointsToAdd;
	OnTeamScoreUpdatedDelegate.Broadcast(TeamData.TeamScore);
}


void UTeamManager::SetTeamData(const FTeamMatchData& NewTeamData){TeamData = NewTeamData;}
void UTeamManager::AddRacerStatsLine(ULeague_RacerStatsLine* RacerStatsLine){RacerStatsLines.Add(RacerStatsLine);}
TArray<ULeague_RacerStatsLine*>& UTeamManager::GetRacerStatsLines(){return RacerStatsLines;}
bool UTeamManager::IsVisitorTeam()const{return TeamData.IsVisitorTeam;}
TArray<URacerMatchManager*>& UTeamManager::GetRacerManagers() {return TeamData.Racers;}
TMap<int32, TObjectPtr<URacerMatchManager>>& UTeamManager::GetRacers(){return Racers;}
ETeams UTeamManager::GetTeam() const{return TeamData.Team;}
int32 UTeamManager::GetTeamScore() const{return TeamData.TeamScore;}
int32 UTeamManager::GetRaceScore(int32 RaceID) const{return TeamData.EachRaceScore[RaceID];}
FString UTeamManager::GetTeamName() const{return TeamData.GetTeamName();}

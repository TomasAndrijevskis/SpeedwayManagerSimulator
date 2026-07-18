
#include "Managers/MatchManager.h"
#include "Gamemodes/SMS_GameMode.h"
#include "Managers/RaceLineupManager.h"
#include "Managers/RaceManager.h"
#include "Managers/ScoreManager.h"
#include "Managers/TeamManager.h"
#include "UI/League/Program/RacerStatsLine.h"


void UMatchManager::InitializeManager(ASMS_GameMode* CurrentGameMode)
{
	if (!CurrentGameMode) return;
	GameMode = CurrentGameMode;
	ScoreManager = GameMode->GetScoreManager();
	if (!ScoreManager) return;
	BindDelegates();
}


void UMatchManager::BindDelegates()
{
	OnRaceStaredDelegate.AddUObject(this, &UMatchManager::SimulateRace);
}


void UMatchManager::SimulateRace()
{
	if (CurrentRace <= Races.Num())
	{
		if (!Races[CurrentRace].RaceManager->CheckAllRacersInRace()) return;
		BindRaceDelegates();
		Races[CurrentRace].RaceManager->OnSimulateRaceRequestDelegate.Broadcast();
		HandleRaceFinished();
	}
}


void UMatchManager::BindRaceDelegates()
{
	if (!Races[CurrentRace].RaceManager) return;
	Races[CurrentRace].RaceManager->OnRaceScoreUpdatedDelegate.AddUObject(ScoreManager, &UScoreManager::UpdateScore);
}


void UMatchManager::HandleRaceFinished()
{
	ScoreManager->ClearLastRaceScore();
	CurrentRace++;
	if (CurrentRace <= Races.Num())
	{
		Races[CurrentRace].RaceManager->OnChangedRaceStatusRequestDelegate.Broadcast(true);
		bool IsNominatedRace = Races[CurrentRace].RaceManager->IsNominatedRace();
		Races[CurrentRace].RaceLineupManager->OnHandleRaceLinesRequestDelegate.Broadcast(IsNominatedRace);
	}
	else OnMatchEndedDelegate.Broadcast();
}


void UMatchManager::CreateRacerManagers(TArray<UTeamManager*> TeamManagersRef)
{
	if (TeamManagersRef.IsEmpty()) return;
	for (const auto& Manager : TeamManagersRef)
	{
		Manager->CreateRacerManagers();
	}
	PopulateRacers(TeamManagersRef);
	OnRacerManagersCreatedDelegate.Broadcast(TeamManagersRef);
}


void UMatchManager::PopulateRacers(TArray<UTeamManager*> TeamManagersRef)
{
	if (TeamManagersRef.IsEmpty()) return;
	for (const auto& Manager : TeamManagersRef)
	{
		Manager->ForEachRacerInLineup([this, Manager](int RacerNumber)
		{
			for (const auto& RacerStatsLine : Manager->GetRacerStatsLines())
			{
				if (RacerStatsLine->GetID() == RacerNumber)
				{
					if (URacerManager** FoundManager = Manager->GetRacerManagers().Find(RacerNumber))
					{
						RacerStatsLine->InitializeManagers(*FoundManager);
						break;
					}
				}
			}
		});
		Manager->ForEachRacerInLineup([this](URacerManager* RacerManagerRef)
		{
			RequestToAssignRacersToRace(RacerManagerRef);
		});
	}
}


void UMatchManager::AddNewRace(const int RaceId, const FRaceData RaceData)
{
	Races.Add(RaceId, RaceData);
}


void UMatchManager::RequestToAssignRacersToRace(URacerManager* RacerManagerRef)
{
	for (const auto& Race : Races)
	{
		Race.Value.RaceLineupManager->AssignRacerToRace(RacerManagerRef);//!!!!!!!!
	}
}


void UMatchManager::SetTeamID(int NewTeamID, bool IsVisitor)
{
	FTeamMatchData Data = GameMode->GetTeamData(NewTeamID);
	Data.IsVisitorTeam = IsVisitor;
	Teams.Add(Data);
}


FTeamMatchData* UMatchManager::GetTeamData(bool Status)
{
	for (auto& Team : Teams)
	{
		if (Team.IsVisitorTeam == Status) return &Team;
	}
	return nullptr;
}


int UMatchManager::GetCurrentRaceNumber() const {return CurrentRace;}
int UMatchManager::GetAmountOfRaces() const{return Races.Num();}
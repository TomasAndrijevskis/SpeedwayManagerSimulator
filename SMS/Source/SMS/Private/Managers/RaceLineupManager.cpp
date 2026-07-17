
#include "Managers/RaceLineupManager.h"
#include "Gamemodes/SMS_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/ScoreManager.h"
#include "Managers/TeamManager.h"
#include "UI/League/Program/RaceLineBase.h"


void URaceLineupManager::InitializeManager()
{
	ASMS_GameMode* GameMode = Cast<ASMS_GameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	ScoreManager = GameMode->GetScoreManager();
	BindDelegates();
}


void URaceLineupManager::OnRaceInitialized()
{
	BindRaceLineDelegates();
}

void URaceLineupManager::BindDelegates()
{
	OnHandleRaceLinesRequestDelegate.AddUObject(this, &URaceLineupManager::HandleRaceLines);
}


void URaceLineupManager::BindRaceLineDelegates()
{
	for (const auto& RaceLine : RaceLines)
	{
		RaceLine->OnRacerReplacedDelegate.AddUObject(this, &URaceLineupManager::OnRacerReplaced);
		RaceLine->OnRacerChosenDelegate.AddUObject(this, &URaceLineupManager::OnRacerChosen);
	}
}


void URaceLineupManager::HandleRaceLines(bool IsNominatedRace)
{
	if (RaceLines.IsEmpty()) return;
	for (const auto& RaceLine : RaceLines)
	{
		DeniedOptions.Add(RaceLine->GetRacerManager());
	}
	for (const auto& RaceLine : RaceLines)
	{
		FillOptions(IsTeamLosing(RaceLine), IsNominatedRace, RaceLine->GetTeamManager(), RaceLine);
	}
	HandleAddedOptions();
}


void URaceLineupManager::FillOptions(bool IsTeamLosing, bool IsNominatedRace, UTeamManager* TeamManagerRef, const URaceLineBase* RaceLineRef)
{
	if (!TeamManagerRef || !RaceLineRef) return;
	TeamManagerRef->GetAvailableReplacementRacers(IsTeamLosing, IsNominatedRace, RaceLineRef->GetRacerManager(), [this](URacerManager* RacerManager)
	{
		if (!DeniedOptions.Contains(RacerManager) && !RacerOptions.Contains(RacerManager))
			AddOption(RacerManager);
	});
}


void URaceLineupManager::AddOption(URacerManager* NewRacerManager)
{
	RacerOptions.Add(NewRacerManager);
}


void URaceLineupManager::HandleAddedOptions()
{
	if (RacerOptions.IsEmpty()) return;
	for (const auto& Line : RaceLines)
	{
		for (const auto& Racer : RacerOptions)
		{
			if (Line->GetRaceLineData().IsVisitorLine() == Racer->IsVisitor())
			{
				Line->AddOption(Racer->GetRacerName());
				Line->ChangeChooseBoxStatus(true);
			}
		}
	}
}


void URaceLineupManager::AddRaceLine(URaceLineBase* NewRaceLine)
{
	RaceLines.Add(NewRaceLine);
}


void URaceLineupManager::OnRacerChosen(URaceLineBase* RaceLineRef, const FString& RacerName)
{
	for (auto& RaceLine : RaceLines)
	{
		if (RaceLine != RaceLineRef) RaceLine->RemoveFromMainSelection(RacerName);
		RaceLine->RemoveFromReplacementSelection(RacerName);
		
	}
	FindSelectedRacer(RacerName, [RaceLineRef](URacerManager* Manager)
	{
		RaceLineRef->SetRacerData(Manager, false);
		RaceLineRef->SetRacerNumber(Manager->GetRacerNumber());
		RaceLineRef->LockChosenRacer();
	});
}


void URaceLineupManager::OnRacerReplaced(URaceLineBase* RaceLineRef, const FString& RacerName)
{
	for (auto& RaceLine : RaceLines)
	{
		if (RaceLine != RaceLineRef)
		{
			RaceLine->RemoveFromReplacementSelection(RacerName);
			RaceLine->RemoveFromMainSelection(RacerName);
		}
	}
	FindSelectedRacer(RacerName, [this, RaceLineRef](URacerManager* Manager)
	{
		RaceLineRef->GetRacerManager()->RemoveParticipatedRace(RaceLineRef);
		RaceLineRef->SetRacerData(Manager, true);
	});
}


void URaceLineupManager::FindSelectedRacer(const FString& SelectedItem, const TFunction<void(URacerManager*)>& Callback)
{
	for (const auto& Manager : RacerOptions)
	{
		if (Manager->GetRacerName() == SelectedItem)
		{
			Callback(Manager);
			return;
		}
	}
}


void URaceLineupManager::AssignRacerToRace(URacerManager* RacerManagerRef)
{
	for (const auto& RaceLine : RaceLines)
	{
		if (RaceLine->GetRacerNumber() == RacerManagerRef->GetRacerNumber())
			RaceLine->SetRacerData(RacerManagerRef, false);
	}
}


bool URaceLineupManager::IsTeamLosing(URaceLineBase* RaceLineRef) const
{
	if (!ScoreManager) return false;
	const int OwnTeamScore = ScoreManager->GetTeamScore(RaceLineRef->GetRaceLineData().IsVisitorLine());
	const int EnemyTeamScore = ScoreManager->GetTeamScore(!RaceLineRef->GetRaceLineData().IsVisitorLine());
	return EnemyTeamScore >= OwnTeamScore + 6;
}
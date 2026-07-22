
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
	OnHandleRaceLinesRequestDelegate.AddUObject(this, &URaceLineupManager::InitializeRaceLineOptions);
}


void URaceLineupManager::BindRaceLineDelegates()
{
	for (const auto& RaceLine : RaceLines)
	{
		RaceLine->OnRacerReplacedDelegate.AddUObject(this, &URaceLineupManager::OnRacerReplaced);
		RaceLine->OnRacerChosenDelegate.AddUObject(this, &URaceLineupManager::OnRacerChosen);
		RaceLine->OnSelectedRacerChangedDelegate.AddUObject(this, &URaceLineupManager::RestoreRacerAvailability);
	}
}


void URaceLineupManager::InitializeRaceLineOptions(bool IsNominatedRace)
{
	if (RaceLines.IsEmpty()) return;
	if (!IsNominatedRace)
	{
		for (const auto& RaceLine : RaceLines)
		{
			UnavailableOptions.Add(RaceLine->GetRacerManager());
		}
	}
	BuildAvailableRacersLists(IsNominatedRace);
}


void URaceLineupManager::BuildAvailableRacersLists(bool IsNominatedRace)
{
	for (const auto& RaceLine : RaceLines)
	{
		FillAvailableRacers(IsTeamLosing(RaceLine), IsNominatedRace, RaceLine->GetTeamManager(), RaceLine);
	}
	UpdateSelectionWidgets(IsNominatedRace);
}


void URaceLineupManager::FillAvailableRacers(bool IsTeamLosing, bool IsNominatedRace, UTeamManager* TeamManagerRef, const URaceLineBase* RaceLineRef)
{
	if (!TeamManagerRef || !RaceLineRef) return;
	TeamManagerRef->GetAvailableReplacementRacers(IsTeamLosing, RaceLineRef->GetRacerManager(), [this](URacerManager* RacerManager)
	{
		if (!UnavailableOptions.Contains(RacerManager) && !AvailableReplacementRacers.Contains(RacerManager)) RegisterAvailableReplacementRacer(RacerManager);
	});
	if (IsNominatedRace)
	{
		TeamManagerRef->GetAvailableRacers(RaceLineRef->GetRacerManager(), [this](URacerManager* RacerManager)
		{
			if (!UnavailableOptions.Contains(RacerManager) && !AvailableMainRacers.Contains(RacerManager)) RegisterAvailableMainRacer(RacerManager);
		});
	}
}


void URaceLineupManager::RegisterAvailableReplacementRacer(URacerManager* NewRacerManager)
{
	AvailableReplacementRacers.Add(NewRacerManager);
}


void URaceLineupManager::RegisterAvailableMainRacer(URacerManager* NewRacerManager)
{
	AvailableMainRacers.Add(NewRacerManager);
}


void URaceLineupManager::UpdateSelectionWidgets(bool IsNominatedRace)
{
	for (const auto& Line : RaceLines)
	{
		if (IsNominatedRace)
		{
			FillOptionsInComboBox(AvailableMainRacers, *Line, [](URaceLineBase& Line, const FString& Name)
			{
				Line.AddMainOption(Name);
			});
		}
		FillOptionsInComboBox(AvailableReplacementRacers, *Line, [](URaceLineBase& Line, const FString& Name)
		{
			Line.AddReplacementOption(Name);
		});
	}
}


void URaceLineupManager::FillOptionsInComboBox(TArray<URacerManager*>& OptionsArray, URaceLineBase& RaceLineRef, TFunction<void(URaceLineBase&, const FString&)> AddOption)
{
	if (OptionsArray.IsEmpty()) return;
	for (const auto& Racer : OptionsArray)
	{
		if (RaceLineRef.GetRaceLineData().IsVisitorLine() == Racer->IsVisitor())
		{
			AddOption(RaceLineRef, Racer->GetRacerName());
			RaceLineRef.ChangeChooseBoxStatus(true);
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
	FindSelectedRacerByName(RacerName, AvailableMainRacers, [this, RaceLineRef](URacerManager* Manager)
	{
		RaceLineRef->SetRacerData(Manager, false);
		RaceLineRef->SetRacerNumber(Manager->GetRacerNumber());
		AvailableMainRacers.Remove(Manager);
		UnavailableOptions.Add(Manager);
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
	FindSelectedRacerByName(RacerName, AvailableReplacementRacers, [this, RaceLineRef](URacerManager* Manager)
	{
		RaceLineRef->GetRacerManager()->RemoveParticipatedRace(RaceLineRef);
		RaceLineRef->SetRacerData(Manager, true);
		AvailableReplacementRacers.Remove(Manager);
		UnavailableOptions.Add(Manager);
	});
}


void URaceLineupManager::RestoreRacerAvailability(URaceLineBase* RaceLineRef, URacerManager* RacerManagerRef)
{
	if (UnavailableOptions.Contains(RacerManagerRef)) UnavailableOptions.Remove(RacerManagerRef);
	RacerManagerRef->RemoveParticipatedRace(RaceLineRef);
	AvailableReplacementRacers.Empty();
	AvailableMainRacers.Empty();
	BuildAvailableRacersLists(true);
}


void URaceLineupManager::FindSelectedRacerByName(const FString& SelectedItem, TArray<URacerManager*>& OptionsArray, const TFunction<void(URacerManager*)>& Callback)
{
	if (OptionsArray.IsEmpty()) return;
	for (const auto& Manager : OptionsArray)
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
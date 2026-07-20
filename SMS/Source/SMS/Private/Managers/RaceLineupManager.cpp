
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
	if (!IsNominatedRace)
	{
		for (const auto& RaceLine : RaceLines)
		{
			DeniedOptions.Add(RaceLine->GetRacerManager());
		}
	}
	HandleOptions(IsNominatedRace);
}


void URaceLineupManager::HandleOptions(bool IsNominatedRace)
{
	for (const auto& RaceLine : RaceLines)
	{
		FillOptions(IsTeamLosing(RaceLine), IsNominatedRace, RaceLine->GetTeamManager(), RaceLine);
	}
	HandleAddedOptions(IsNominatedRace);
}


void URaceLineupManager::FillOptions(bool IsTeamLosing, bool IsNominatedRace, UTeamManager* TeamManagerRef, const URaceLineBase* RaceLineRef)
{
	if (!TeamManagerRef || !RaceLineRef) return;
	TeamManagerRef->GetAvailableReplacementRacers(IsTeamLosing, RaceLineRef->GetRacerManager(), [this](URacerManager* RacerManager)
	{
		if (!DeniedOptions.Contains(RacerManager) && !RacerReplacementOptions.Contains(RacerManager))
			AddReplacementOption(RacerManager);
	});
	if (IsNominatedRace)
	{
		TeamManagerRef->GetAvailableRacers(RaceLineRef->GetRacerManager(), [this](URacerManager* RacerManager)
		{
			if (!RacerMainOptions.Contains(RacerManager))
				AddMainOption(RacerManager);
		});
	}
}


void URaceLineupManager::AddReplacementOption(URacerManager* NewRacerManager)
{
	RacerReplacementOptions.Add(NewRacerManager);
}


void URaceLineupManager::AddMainOption(URacerManager* NewRacerManager)
{
	RacerMainOptions.Add(NewRacerManager);
}


void URaceLineupManager::HandleAddedOptions(bool IsNominatedRace)
{
	if (RacerReplacementOptions.IsEmpty()) return;
	for (const auto& Line : RaceLines)
	{
		if (IsNominatedRace)
		{
			FillOptionsInWidget(RacerMainOptions, *Line, [](URaceLineBase& Line, const FString& Name)
			{
				Line.AddMainOption(Name);
			});
		}
		FillOptionsInWidget(RacerReplacementOptions, *Line, [](URaceLineBase& Line, const FString& Name)
		{
			Line.AddReplacementOption(Name);
		});
	}
}


void URaceLineupManager::FillOptionsInWidget(TArray<URacerManager*>& OptionsArray, URaceLineBase& RaceLineRef, TFunction<void(URaceLineBase&, const FString&)> AddOption)
{
	if (OptionsArray.IsEmpty()) return;
	for (const auto& Racer : OptionsArray)
	{
		if (RaceLineRef.GetRaceLineData().IsVisitorLine() == Racer->IsVisitor())
		{
			AddOption(RaceLineRef, Racer->GetRacerName());
			//RaceLineRef.AddMainOption(Racer->GetRacerName());
			//RaceLineRef.AddReplacementOption(Racer->GetRacerName());
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
	FindSelectedRacer(RacerName, RacerMainOptions, [RaceLineRef](URacerManager* Manager)
	{
		RaceLineRef->SetRacerData(Manager, false);
		RaceLineRef->SetRacerNumber(Manager->GetRacerNumber());
		RaceLineRef->LockChosenRacer();//!!!!!!!!!!!!!!!
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
	FindSelectedRacer(RacerName, RacerReplacementOptions, [this, RaceLineRef](URacerManager* Manager)
	{
		RaceLineRef->GetRacerManager()->RemoveParticipatedRace(RaceLineRef);
		RaceLineRef->SetRacerData(Manager, true);
	});
}


void URaceLineupManager::FindSelectedRacer(const FString& SelectedItem, TArray<URacerManager*>& OptionsArray, const TFunction<void(URacerManager*)>& Callback)
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
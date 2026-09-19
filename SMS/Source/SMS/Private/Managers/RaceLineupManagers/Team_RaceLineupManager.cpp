
#include "Managers/RaceLineupManagers/Team_RaceLineupManager.h"
#include "Managers/TeamManager.h"
#include "Rules/League_Rules.h"
#include "Subsystems/MatchManagerSubsystem.h"
#include "UI/BaseClasses/RaceLine_Base.h"
#include "UI/League/Program/Race/League_RaceLine_Base.h"


void UTeam_RaceLineupManager::OnRaceInitialized()
{
	BindRaceLineDelegates();
}


void UTeam_RaceLineupManager::BindDelegates()
{
	OnHandleRaceLinesDelegate.AddUObject(this, &UTeam_RaceLineupManager::InitializeRaceLineOptions);
}


void UTeam_RaceLineupManager::BindRaceLineDelegates()
{
	for (const auto& RaceLine : RaceLines)
	{
		if (ULeague_RaceLine_Base* RL = Cast<ULeague_RaceLine_Base>(RaceLine))
		{
			RL->OnRacerReplacedDelegate.AddUObject(this, &UTeam_RaceLineupManager::OnRacerReplaced);
			RL->OnRacerChosenDelegate.AddUObject(this, &UTeam_RaceLineupManager::OnRacerChosen);
			RL->OnSelectedRacerChangedDelegate.AddUObject(this, &UTeam_RaceLineupManager::RestoreRacerAvailability);
		}
	}
}


void UTeam_RaceLineupManager::InitializeRaceLineOptions(bool IsNominatedRace)
{
	if (RaceLines.IsEmpty()) return;
	if (!IsNominatedRace)
	{
		for (const auto& RaceLine : RaceLines)
		{
			PossibleRacers.Add(RaceLine->GetRacerManager());
		}
	}
	BuildAvailableRacersLists(IsNominatedRace);
}


void UTeam_RaceLineupManager::BuildAvailableRacersLists(bool IsNominatedRace)
{
	for (const auto& RaceLine : RaceLines)
	{
		if (!IsNominatedRace) UnavailableRacers.Add(RaceLine->GetRacerManager());
	}
	for (const auto& RaceLine : RaceLines)
	{
		if (ULeague_RaceLine_Base* RL = Cast<ULeague_RaceLine_Base>(RaceLine))
		{
			if (IsNominatedRace) FillPossibleMainRacers(RL);
			if (!IsNominatedRace) FillPossibleReplacementRacers(RL);
		}
	}
}


void UTeam_RaceLineupManager::FillPossibleReplacementRacers(const ULeague_RaceLine_Base* RaceLineRef)
{
	if (!RaceLineRef) return;
	if (UMatchManagerSubsystem* MatchManagerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMatchManagerSubsystem>())
	{
		if(UTeamManager* TeamManager = Cast<ULeague_Rules>(MatchManagerSubsystem->GetCompetitionRules())->GetTeamManager(RaceLineRef->IsVisitor()))
		{
			URacerMatchManager* OriginalRacer = RaceLineRef->GetOriginalRacerManager();
			TeamManager->GetAvailableReplacementRacers(OriginalRacer, [this, OriginalRacer](const TObjectPtr<URacerMatchManager>& ReplacementRacer)
			{
				if (!UnavailableRacers.Contains(ReplacementRacer)) PossibleRacers.FindOrAdd(OriginalRacer).Add(ReplacementRacer);
			});
			UpdateReplacementSelectionWidgets();
		}
	}
}


void UTeam_RaceLineupManager::FillPossibleMainRacers(const ULeague_RaceLine_Base* RaceLineRef)
{
	if (!RaceLineRef) return;
	if (UMatchManagerSubsystem* MatchManagerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMatchManagerSubsystem>())
	{
		if(UTeamManager* TeamManager = Cast<ULeague_Rules>(MatchManagerSubsystem->GetCompetitionRules())->GetTeamManager(RaceLineRef->IsVisitor()))
		{
			TeamManager->GetAvailableRacers([this](URacerMatchManager* RacerManager)
			{
				if (!PossibleRacers.Contains(RacerManager)) PossibleRacers.FindOrAdd(RacerManager);
			});
			UpdateMainSelectionWidgets();
		}
	}
}


void UTeam_RaceLineupManager::UpdateReplacementSelectionWidgets()
{
	for (const auto& RaceLine : RaceLines)
	{
		if (ULeague_RaceLine_Base* RL = Cast<ULeague_RaceLine_Base>(RaceLine))
		{
			if (!RL->GetOriginalRacerManager()) continue;
			FillOptionsInComboBox(PossibleRacers[RL->GetOriginalRacerManager()], *RL, [](ULeague_RaceLine_Base& Line, const FString& Name)
			{
				Line.AddReplacementOption(Name);
			});
		}
		
	}
}


void UTeam_RaceLineupManager::UpdateMainSelectionWidgets()
{
	for (const auto& RaceLine : RaceLines)
	{
		if (ULeague_RaceLine_Base* RL = Cast<ULeague_RaceLine_Base>(RaceLine))
		{
			TArray<TObjectPtr<URacerMatchManager>> Keys;
			PossibleRacers.GetKeys(Keys);
			FillOptionsInComboBox(Keys, *RL, [](ULeague_RaceLine_Base& RL, const FString& Name)
			{
				RL.AddMainOption(Name);
			});
		}
		
	}
}


void UTeam_RaceLineupManager::FillOptionsInComboBox(TArray<TObjectPtr<URacerMatchManager>>& RacerArray, ULeague_RaceLine_Base& RaceLineRef, TFunction<void(ULeague_RaceLine_Base&, const FString&)> AddOption)
{
	if (RacerArray.IsEmpty()) return;
	for (const auto& Racer : RacerArray)
	{
		if (!Racer || UnavailableRacers.Contains(Racer)) continue;
		if (RaceLineRef.IsVisitor() == Racer->IsVisitor())
		{
			AddOption(RaceLineRef, Racer->GetRacerName());
			RaceLineRef.ChangeChooseBoxStatus(true);
		}
	}
}



void UTeam_RaceLineupManager::OnRacerChosen(ULeague_RaceLine_Base* RaceLineRef, const FString& RacerName)
{
	UE_LOG(LogTemp, Display, TEXT("OnRacerChosen %s"), *RacerName);
	for (const auto& RaceLine : RaceLines)
	{
		if (ULeague_RaceLine_Base* RL = Cast<ULeague_RaceLine_Base>(RaceLine))
		{
			if (RL != RaceLineRef) RL->RemoveFromMainSelection(RacerName);
			RL->RemoveFromReplacementSelection(RacerName);
		}
	}
	TArray<TObjectPtr<URacerMatchManager>> Keys;
	PossibleRacers.GetKeys(Keys);
	FindSelectedRacerByName(RacerName, Keys, [this, RaceLineRef](URacerMatchManager* RacerManager)
	{
		RaceLineRef->SetRacerData(RacerManager, false);
		RaceLineRef->SetRacerNumber(RacerManager->GetRacerNumber());
		RacerManager->SetParticipatedInNominatedRace(true);
		UnavailableRacers.Add(RacerManager);
	});
	FillPossibleReplacementRacers(RaceLineRef);
}


void UTeam_RaceLineupManager::OnRacerReplaced(ULeague_RaceLine_Base* RaceLineRef, const FString& RacerName, URacerMatchManager* OriginalRacerManager)
{
	for (const auto& RaceLine : RaceLines)
	{
		if (ULeague_RaceLine_Base* RL = Cast<ULeague_RaceLine_Base>(RaceLine))
		{
			if (RL != RaceLineRef)
			{
				RL->RemoveFromReplacementSelection(RacerName);
				RL->RemoveFromMainSelection(RacerName);
			}
		}
	}
	FindSelectedRacerByName(RacerName, PossibleRacers[OriginalRacerManager], [this, RaceLineRef](URacerMatchManager* RacerManager)
	{
		RacerManager->IncreaseAmountOfReplacements();
		RaceLineRef->GetRacerManager()->RemoveParticipatedRace(RaceLineRef->GetRaceID());
		RaceLineRef->SetRacerData(RacerManager, true);
		UnavailableRacers.Add(RacerManager);
	});
}


void UTeam_RaceLineupManager::RestoreRacerAvailability(ULeague_RaceLine_Base* RaceLineRef, URacerMatchManager* RacerManager, bool bIsReplacement)
{
	if (bIsReplacement) RacerManager->DecreaseAmountOfReplacements();
	RacerManager->RemoveParticipatedRace(RaceLineRef->GetRaceID());
	RacerManager->SetParticipatedInNominatedRace(false);
	UnavailableRacers.Remove(RacerManager);
	UpdateMainSelectionWidgets();
	UpdateReplacementSelectionWidgets();
}


void UTeam_RaceLineupManager::FindSelectedRacerByName(const FString& SelectedItem, TArray<TObjectPtr<URacerMatchManager>>& OptionsArray, const TFunction<void(URacerMatchManager*)>& Callback)
{
	if (OptionsArray.IsEmpty()) return;
	for (const auto& RacerManager : OptionsArray)
	{
		if (RacerManager->GetRacerName() == SelectedItem)
		{
			Callback(RacerManager);
			return;
		}
	}
}

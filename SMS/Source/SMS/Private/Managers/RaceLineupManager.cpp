
#include "Managers/RaceLineupManager.h"
#include "Managers/TeamManager.h"
#include "Rules/League_Rules.h"
#include "Subsystems/MatchManagerSubsystem.h"
#include "UI/League/Program/Race/League_RaceLine_Base.h"


void URaceLineupManager::InitializeManager()
{
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
			PossibleRacers.Add(RaceLine->GetRacerManager());
		}
	}
	BuildAvailableRacersLists(IsNominatedRace);
}


void URaceLineupManager::BuildAvailableRacersLists(bool IsNominatedRace)
{
	for (const auto& RaceLine : RaceLines)
	{
		if (!IsNominatedRace) UnavailableRacers.Add(RaceLine->GetRacerManager());
	}
	for (const auto& RaceLine : RaceLines)
	{
		if (IsNominatedRace) FillPossibleMainRacers(RaceLine);
		if (!IsNominatedRace) FillPossibleReplacementRacers(RaceLine);
	}
}


void URaceLineupManager::FillPossibleReplacementRacers(const ULeague_RaceLine_Base* RaceLineRef)
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


void URaceLineupManager::FillPossibleMainRacers(const ULeague_RaceLine_Base* RaceLineRef)
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


void URaceLineupManager::UpdateReplacementSelectionWidgets()
{
	for (const auto& Line : RaceLines)
	{
		if (!Line->GetOriginalRacerManager()) continue;
		FillOptionsInComboBox(PossibleRacers[Line->GetOriginalRacerManager()], *Line, [](ULeague_RaceLine_Base& Line, const FString& Name)
		{
			Line.AddReplacementOption(Name);
		});
	}
}


void URaceLineupManager::UpdateMainSelectionWidgets()
{
	for (const auto& Line : RaceLines)
	{
		TArray<TObjectPtr<URacerMatchManager>> Keys;
		PossibleRacers.GetKeys(Keys);
		FillOptionsInComboBox(Keys, *Line, [](ULeague_RaceLine_Base& Line, const FString& Name)
		{
			Line.AddMainOption(Name);
		});
	}
}


void URaceLineupManager::FillOptionsInComboBox(TArray<TObjectPtr<URacerMatchManager>>& RacerArray, ULeague_RaceLine_Base& RaceLineRef, TFunction<void(ULeague_RaceLine_Base&, const FString&)> AddOption)
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


void URaceLineupManager::AddRaceLine(ULeague_RaceLine_Base* NewRaceLine)
{
	RaceLines.Add(NewRaceLine);
}


void URaceLineupManager::OnRacerChosen(ULeague_RaceLine_Base* RaceLineRef, const FString& RacerName)
{
	UE_LOG(LogTemp, Display, TEXT("OnRacerChosen %s"), *RacerName);
	for (auto& RaceLine : RaceLines)
	{
		if (RaceLine != RaceLineRef) RaceLine->RemoveFromMainSelection(RacerName);
		RaceLine->RemoveFromReplacementSelection(RacerName);
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


void URaceLineupManager::OnRacerReplaced(ULeague_RaceLine_Base* RaceLineRef, const FString& RacerName, URacerMatchManager* OriginalRacerManager)
{
	for (auto& RaceLine : RaceLines)
	{
		if (RaceLine != RaceLineRef)
		{
			RaceLine->RemoveFromReplacementSelection(RacerName);
			RaceLine->RemoveFromMainSelection(RacerName);
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


void URaceLineupManager::RestoreRacerAvailability(ULeague_RaceLine_Base* RaceLineRef, URacerMatchManager* RacerManager, bool bIsReplacement)
{
	if (bIsReplacement) RacerManager->DecreaseAmountOfReplacements();
	RacerManager->RemoveParticipatedRace(RaceLineRef->GetRaceID());
	RacerManager->SetParticipatedInNominatedRace(false);
	UnavailableRacers.Remove(RacerManager);
	UpdateMainSelectionWidgets();
	UpdateReplacementSelectionWidgets();
}


void URaceLineupManager::FindSelectedRacerByName(const FString& SelectedItem, TArray<TObjectPtr<URacerMatchManager>>& OptionsArray, const TFunction<void(URacerMatchManager*)>& Callback)
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


void URaceLineupManager::AssignRacerToRace(URacerMatchManager* RacerManager)
{
	for (const auto& RaceLine : RaceLines)
	{
		if (RaceLine->GetRacerNumber() == RacerManager->GetRacerNumber())
			RaceLine->SetRacerData(RacerManager, false);
	}
}
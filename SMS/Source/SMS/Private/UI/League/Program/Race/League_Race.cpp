
#include "SMS/Public/UI/League/Program/Race/League_Race.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Data/RaceData/RacePatternsDataAsset.h"
#include "Managers/RaceLineupManagers/Team_RaceLineupManager.h"
#include "Managers/RaceManagers/League_RaceManager.h"
#include "Rules/League_Rules.h"
#include "Subsystems/MatchManagerSubsystem.h"
#include "UI/League/Program/ScoreCounter.h"
#include "UI/League/Program/Race/NominatedRaceLine.h"
#include "UI/League/Program/Race/RaceLine.h"


void ULeague_Race::InitializeWidget(int32 NewID)
{
	Super::InitializeWidget(NewID);
}


void ULeague_Race::InitializeRaceData()
{
	Super::InitializeRaceData();
	FRaceData data;
	data.RaceManager = NewObject<ULeague_RaceManager>(this);
	data.RaceLineupManager = NewObject<UTeam_RaceLineupManager>(this);
	if (!data.RaceManager || !data.RaceLineupManager) return;
	data.RaceManager->InitializeManager(IsNominatedRace(), RaceID);
	data.RaceLineupManager->InitializeManager();
	Data = data;
}


void ULeague_Race::BindDelegates()
{
	Super::BindDelegates();
	if (!Data.RaceManager) return;
	Data.RaceManager->OnRaceFinishedDelegate.AddUObject(this, &ULeague_Race::UpdateScore);
	Data.RaceManager->OnRaceLineResultUpdatedDelegate.AddUObject(this, &URace_Base::OnRaceStatsUpdateRequested);
}


void ULeague_Race::CreateRaceLines()
{
	if (!Data.RaceManager || !Data.RaceLineupManager || !RacePatternDataAsset) return;
	const int32 RaceLineAmount = RacePatternDataAsset->RacePatterns[RaceID].RaceLines.Num();
	for (int32 RaceLineID = 0; RaceLineID < RaceLineAmount; RaceLineID++)
	{
		ULeague_RaceLine_Base* NewRaceLine;
		if (!IsNominatedRace()) NewRaceLine = CreateRaceLine(RaceLineID);
		else NewRaceLine = CreateNominatedRaceLine(RaceLineID);
		if (NewRaceLine)
		{
			UVerticalBoxSlot* VB_Slot = VB_Content->AddChildToVerticalBox(NewRaceLine);
			if (VB_Slot)
			{
				VB_Slot->SetHorizontalAlignment(HAlign_Fill);
				VB_Slot->SetVerticalAlignment(VAlign_Fill);
			}
			NewRaceLine->SetRaceLineData(GetRaceLineData(RaceLineID));
			NewRaceLine->OnRacerSetDelegate.AddUObject(Data.RaceManager, &URaceManager_Base::AddRacerManager);
			NewRaceLine->OnRacerRemovedDelegate.AddUObject(Cast<ULeague_RaceManager>(Data.RaceManager), &ULeague_RaceManager::RemoveRacerManager);
			NewRaceLine->OnRequestRaceLinePointsDelegate.BindUObject(Data.RaceManager, &URaceManager_Base::GetRaceLinePoints);
			Data.RaceManager->OnRaceFinishedDelegate.AddUObject(NewRaceLine, &URaceLine_Base::OnRaceFinished);
			Data.RaceManager->OnChangedRaceStatusDelegate.AddUObject(NewRaceLine, &URaceLine_Base::ChangeLineStatus);
			Data.RaceLineupManager->AddRaceLine(NewRaceLine);
		}
	}
	Cast<UTeam_RaceLineupManager>(Data.RaceLineupManager)->OnRaceInitialized();
}


ULeague_RaceLine_Base* ULeague_Race::CreateRaceLine(int32 NewRaceLineID)
{
	if (!RaceLineClass) return nullptr;
	ULeague_RaceLine_Base* NewRaceLine = CreateWidget<ULeague_RaceLine_Base>(this, RaceLineClass);
	if (!NewRaceLine) return nullptr;
	NewRaceLine->SetIDs(NewRaceLineID, RaceID);
	return NewRaceLine;
}


ULeague_RaceLine_Base* ULeague_Race::CreateNominatedRaceLine(int32 NewRaceLineID)
{
	if (!NominatedRaceLineClass) return nullptr;
	UNominatedRaceLine* NewRaceLine = CreateWidget<UNominatedRaceLine>(this, NominatedRaceLineClass);
	if (!NewRaceLine) return nullptr;
	NewRaceLine->SetIDs(NewRaceLineID, RaceID);
	return NewRaceLine;
}


void ULeague_Race::UpdateScore()
{
	if (UMatchManagerSubsystem* MatchManagerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMatchManagerSubsystem>())
	{
		if (ULeague_Rules* Rules = Cast<ULeague_Rules>(MatchManagerSubsystem->GetCompetitionRules()))
		{
			ScoreCounter->SetOverallScore(Rules->GetTeamScore(false),Rules->GetTeamScore(true));
			ScoreCounter->SetRacePoints(Rules->GetTeamRaceScore(false, RaceID), Rules->GetTeamRaceScore(true, RaceID));
		}
	}
}
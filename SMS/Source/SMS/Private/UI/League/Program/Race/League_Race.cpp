
#include "SMS/Public/UI/League/Program/Race/League_Race.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Data/RaceData/RacePatternsDataAsset.h"
#include "Managers/RaceLineupManager.h"
#include "Managers/RaceManager.h"
#include "Rules/LeagueRules.h"
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
	data.RaceManager = NewObject<URaceManager>(this);
	data.RaceLineupManager = NewObject<URaceLineupManager>(this);
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
			Data.RaceManager->AddRaceLine(NewRaceLine);
			Data.RaceLineupManager->AddRaceLine(NewRaceLine);
		}
	}
	Data.RaceLineupManager->OnRaceInitialized();
}


ULeague_RaceLine_Base* ULeague_Race::CreateRaceLine(int32 RaceLineID)
{
	if (!RaceLineClass) return nullptr;
	ULeague_RaceLine_Base* NewRaceLine = CreateWidget<ULeague_RaceLine_Base>(this, RaceLineClass);
	if (!NewRaceLine) return nullptr;
	NewRaceLine->SetRaceLineID(RaceLineID);
	return NewRaceLine;
}


ULeague_RaceLine_Base* ULeague_Race::CreateNominatedRaceLine(int32 RaceLineID)
{
	if (!NominatedRaceLineClass) return nullptr;
	UNominatedRaceLine* NewRaceLine = CreateWidget<UNominatedRaceLine>(this, NominatedRaceLineClass);
	if (!NewRaceLine) return nullptr;
	NewRaceLine->SetRaceLineID(RaceLineID);
	return NewRaceLine;
}


void ULeague_Race::UpdateScore()
{
	if (UMatchManagerSubsystem* MatchManagerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMatchManagerSubsystem>())
	{
		if (ULeagueRules* Rules = Cast<ULeagueRules>(MatchManagerSubsystem->GetCompetitionRules()))
		{
			ScoreCounter->SetOverallScore(Rules->GetTeamScore(false),Rules->GetTeamScore(true));
			ScoreCounter->SetRacePoints(Rules->GetTeamRaceScore(false, RaceID), Rules->GetTeamRaceScore(true, RaceID));
		}
	}
}
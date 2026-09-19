
#include "UI/GP/Program/Race/GP_Race.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Data/RaceData/RacePatternsDataAsset.h"
#include "Managers/RaceLineupManagers/RaceLineupManager.h"
#include "Managers/RaceManagers/GP_RaceManager.h"
#include "Subsystems/MatchManagerSubsystem.h"
#include "UI/BaseClasses/RaceLine_Base.h"
#include "UI/GP/Program/Race/GP_RaceLine_Base.h"


void UGPRace::InitializeWidget(int32 NewID)
{
	Super::InitializeWidget(NewID);
}


void UGPRace::InitializeRaceData()
{
	Super::InitializeRaceData();
	FRaceData data;
	data.RaceManager = NewObject<UGP_RaceManager>(this);
	data.RaceLineupManager = NewObject<URaceLineupManager>(this);
	if (!data.RaceManager) return;
	data.RaceManager->InitializeManager(IsNominatedRace(), RaceID);
	data.RaceLineupManager->InitializeManager();
	Data = data;
}


void UGPRace::BindDelegates()
{
	Super::BindDelegates();
	if (!Data.RaceManager) return;
	Data.RaceManager->OnRaceLineResultUpdatedDelegate.AddUObject(this, &URace_Base::OnRaceStatsUpdateRequested);
}


void UGPRace::CreateRaceLines()
{
	if (!Data.RaceManager || !RacePatternDataAsset) return;
	const int32 RaceLineAmount = RacePatternDataAsset->RacePatterns[RaceID].RaceLines.Num();
	for (int32 RaceLineID = 0; RaceLineID < RaceLineAmount; RaceLineID++)
	{
		if (UGP_RaceLine_Base* NewRaceLine = CreateRaceLine(RaceLineID))
		{
			if (UVerticalBoxSlot* VB_Slot = VB_Content->AddChildToVerticalBox(NewRaceLine))
			{
				VB_Slot->SetHorizontalAlignment(HAlign_Fill);
				VB_Slot->SetVerticalAlignment(VAlign_Fill);
			}
			NewRaceLine->SetRaceLineData(GetRaceLineData(RaceLineID));
			NewRaceLine->OnRacerSetDelegate.AddUObject(Data.RaceManager, &URaceManager_Base::AddRacerManager);
			NewRaceLine->OnRequestRaceLinePointsDelegate.BindUObject(Data.RaceManager, &URaceManager_Base::GetRaceLinePoints);
			Data.RaceManager->OnRaceFinishedDelegate.AddUObject(NewRaceLine, &URaceLine_Base::OnRaceFinished);
			Data.RaceManager->OnChangedRaceStatusDelegate.AddUObject(NewRaceLine, &URaceLine_Base::ChangeLineStatus);
			Data.RaceLineupManager->AddRaceLine(NewRaceLine);
		}
	}
}


UGP_RaceLine_Base* UGPRace::CreateRaceLine(int32 NewRaceLineID)
{
	if (!RaceLineClass) return nullptr;
	UGP_RaceLine_Base* NewRaceLine = CreateWidget<UGP_RaceLine_Base>(this, RaceLineClass);
	if (!NewRaceLine) return nullptr;
	NewRaceLine->SetIDs(NewRaceLineID, RaceID);
	return NewRaceLine;
}

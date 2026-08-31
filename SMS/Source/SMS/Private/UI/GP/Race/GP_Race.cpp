
#include "UI/GP/Race/GP_Race.h"
#include "Managers/RaceManager.h"


void UGPRace::InitializeWidget(int32 NewID, UScoreManager* ScoreManagerRef)
{
	Super::InitializeWidget(NewID, ScoreManagerRef);
}


void UGPRace::InitializeRaceData()
{
	Super::InitializeRaceData();
	FRaceData data;
	data.RaceManager = NewObject<URaceManager>(this);
	if (!data.RaceManager) return;
	data.RaceManager->InitializeManager();
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
	Super::CreateRaceLines();
}

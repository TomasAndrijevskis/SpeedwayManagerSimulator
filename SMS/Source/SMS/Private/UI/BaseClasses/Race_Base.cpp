
#include "UI/BaseClasses/Race_Base.h"
#include "Data/RaceData/RacePatternsDataAsset.h"
#include "Managers/RaceManager.h"
#include "UI/BaseClasses/NumbersBox.h"


void URace_Base::InitializeWidget(int32 NewID)
{
	RaceID = NewID;
	NumbersBox_RaceNumber->SetText(RaceID);
	InitializeRaceData();
	BindDelegates();
	OnIDSet();
}


void URace_Base::OnRaceStatsUpdateRequested(const TArray<FRaceResultData>& RaceResultData) const
{
	OnRaceStatsUpdateRequestedDelegate.Broadcast(RaceResultData);
}


void URace_Base::OnIDSet()
{
	CreateRaceLines();
	if (RaceID != 1) Data.RaceManager->OnChangedRaceStatusRequestDelegate.Broadcast(false);
}


void URace_Base::SetRacePatternDataAsset(URacePatternsDataAsset* DataAsset){RacePatternDataAsset = DataAsset;}
bool URace_Base::IsNominatedRace() const{return RacePatternDataAsset->RacePatterns[RaceID].IsNominatedRace;}
FRaceData& URace_Base::GetRaceData() {return Data;}
FRaceLineData& URace_Base::GetRaceLineData(int32 RaceLineId) const{return RacePatternDataAsset->RacePatterns[RaceID].RaceLines[RaceLineId];}
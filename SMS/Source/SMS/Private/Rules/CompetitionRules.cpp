
#include "Rules/CompetitionRules.h"
#include "Data/RaceData/RaceData.h"
#include "Managers/TrackManager.h"
#include "Managers/RaceLineupManagers/RaceLineupManager.h"
#include "Managers/RaceManagers/RaceManager_Base.h"


void UCompetitionRules::BindDelegates()
{
	OnRaceStartedDelegate.AddUObject(this, &UCompetitionRules::SimulateRace);
	OnRacingFinishedDelegate.AddUObject(this, &UCompetitionRules::PrepareToEndMatch);
}


void UCompetitionRules::AddNewRace(int32 RaceId, FRaceData RaceData)
{
	Races.Add(RaceId, RaceData);
}


void UCompetitionRules::RequestToAssignRacersToRace(URacerMatchManager* RacerManager)
{
	for (const auto& Race : Races)
	{
		Race.Value.RaceLineupManager->AssignRacerToRace(RacerManager);
	}
}


void UCompetitionRules::SimulateRace()
{
	if (CurrentRace <= Races.Num())
	{
		if (!Races[CurrentRace].RaceManager->AreAllRacersSet()) return;
		UE_LOG(LogTemp, Display, TEXT("Race %i"), CurrentRace);
		Races[CurrentRace].RaceManager->OnSimulateRaceDelegate.Broadcast();
		HandleRaceFinished();
	}
}


void UCompetitionRules::HandleRaceFinished()
{
	if (TrackManager) TrackManager->OnTrackUpdateRequestDelegate.Broadcast();
	Races[CurrentRace].RaceManager->OnChangedRaceStatusDelegate.Broadcast(false);
	CurrentRace++;
}


void UCompetitionRules::CreateTrackManager(const FTrackData& TrackData)
{
	TrackManager = NewObject<UTrackManager>(this);
	if (!TrackManager) return;
	TrackManager->InitializeManager(TrackData);
}


void UCompetitionRules::HandleMatchClosed()
{
	Races.Empty();
	TrackManager = nullptr;
	CurrentRace = 1;
	OnRacingFinishedDelegate.Clear();
	OnRaceStartedDelegate.Clear();
}


void UCompetitionRules::EndMatch()
{
	HandleMatchClosed();
	OnMatchClosedDelegate.Broadcast();
}


FString UCompetitionRules::GetRaceResultText(const ERaceResults RaceResult) const
{
	switch (RaceResult)
	{
		case ERaceResults::First:
			return FString::FromInt(3);
		case ERaceResults::Second:
			return FString::FromInt(2);
		case ERaceResults::Third:
			return FString::FromInt(1);
		case ERaceResults::Fourth:
			return FString::FromInt(0);
		case ERaceResults::Defect:
			return "D";
		default: return "DNF";
	}
}


int32 UCompetitionRules::GetRaceResultAsNumber(const ERaceResults RaceResult) const
{
	switch (RaceResult)
	{
		case ERaceResults::First:
			return 3;
		case ERaceResults::Second:
			return 2;
		case ERaceResults::Third:
			return 1;
		case ERaceResults::Fourth:
			return 0;
		default: return 0;
	}
}

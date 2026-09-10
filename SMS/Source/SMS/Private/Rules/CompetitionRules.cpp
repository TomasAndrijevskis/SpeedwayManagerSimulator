
#include "Rules/CompetitionRules.h"
#include "Data/RaceData/RaceData.h"
#include "Managers/RaceLineupManager.h"
#include "Managers/RaceManager.h"
#include "Managers/TrackManager.h"


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
	if (!TrackManager) return;
	if (CurrentRace <= Races.Num())
	{
		if (!Races[CurrentRace].RaceManager->AreAllRacersSet()) return;
		UE_LOG(LogTemp, Display, TEXT("Race %i"), CurrentRace);
		TrackManager->OnTrackUpdateRequestDelegate.Broadcast(CurrentRace);
		Races[CurrentRace].RaceManager->OnSimulateRaceRequestDelegate.Broadcast();
		HandleRaceFinished();
	}
}


void UCompetitionRules::CreateTrackManager(const FTrackData& HomeTeamTrackData)
{
	TrackManager = NewObject<UTrackManager>(this);
	if (!TrackManager) return;
	TrackManager->InitializeManager(HomeTeamTrackData);
}


void UCompetitionRules::HandleRaceFinished()
{
	Races[CurrentRace].RaceManager->OnChangedRaceStatusRequestDelegate.Broadcast(false);
	CurrentRace++;
	if (CurrentRace <= Races.Num())
	{
		Races[CurrentRace].RaceManager->OnChangedRaceStatusRequestDelegate.Broadcast(true);
		bool IsNominatedRace = Races[CurrentRace].RaceManager->IsNominatedRace();
		Races[CurrentRace].RaceLineupManager->OnHandleRaceLinesRequestDelegate.Broadcast(IsNominatedRace);
	}
	else OnRacingFinishedDelegate.Broadcast();
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


int32 UCompetitionRules::GetCurrentRaceNumber() const {return CurrentRace;}
int32 UCompetitionRules::GetAmountOfRaces() const {return Races.Num();}
TObjectPtr<UTrackManager>& UCompetitionRules::GetTrackManager() {return TrackManager;}
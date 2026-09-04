
#include "Rules/CompetitionRules.h"
#include "Data/RaceData/RaceData.h"
#include "Managers/RaceLineupManager.h"
#include "Managers/RaceManager.h"
#include "Managers/TrackManager.h"


void UCompetitionRules::BindDelegates()
{
	OnRaceStartedDelegate.AddUObject(this, &UCompetitionRules::SimulateRace);
}


void UCompetitionRules::AddNewRace(int32 RaceId, FRaceData RaceData)
{
	Races.Add(RaceId, RaceData);
}

void UCompetitionRules::RequestToAssignRacersToRace(URacerManager* RacerManager)
{
	for (const auto& Race : Races)
	{
		Race.Value.RaceLineupManager->AssignRacerToRace(RacerManager);//!!!!!!!!
	}
}


void UCompetitionRules::SimulateRace()
{
	if (!TrackManager) return;
	if (CurrentRace <= Races.Num())
	{
		if (!Races[CurrentRace].RaceManager->CheckAllRacersInRace()) return;
		UE_LOG(LogTemp, Display, TEXT("Race %i"), CurrentRace);
		TrackManager->OnTrackUpdateRequestDelegate.Broadcast(CurrentRace);
		BindRaceDelegates();
		Races[CurrentRace].RaceManager->OnSimulateRaceRequestDelegate.Broadcast(TrackManager);
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
	CurrentRace++;
	if (CurrentRace <= Races.Num())
	{
		Races[CurrentRace].RaceManager->OnChangedRaceStatusRequestDelegate.Broadcast(true);
		bool IsNominatedRace = Races[CurrentRace].RaceManager->IsNominatedRace();
		Races[CurrentRace].RaceLineupManager->OnHandleRaceLinesRequestDelegate.Broadcast(IsNominatedRace);
	}
	else OnMatchEndedDelegate.Broadcast();
}


int32 UCompetitionRules::GetCurrentRaceNumber() const {return CurrentRace;}
int32 UCompetitionRules::GetAmountOfRaces() const {return Races.Num();}
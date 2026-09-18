
#include "Rules/GP_Rules.h"
#include "Gamemodes/SMS_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/RaceLineupManager.h"
#include "Managers/RacerCareerManager.h"
#include "Managers/RacerMatchManager.h"
#include "Managers/RaceManagers/RaceManager_Base.h"
#include "UI/BaseClasses/RaceLine_Base.h"


void UGP_Rules::SetupMatch()
{
	BindDelegates();
	HandleTrack();
	HandleLineup();
}


void UGP_Rules::HandleTrack()
{
	ASMS_GameMode* GameMode = Cast<ASMS_GameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	CreateTrackManager(GameMode->GetTrackData(ECities::Daugavpils));
}


void UGP_Rules::PopulateRacers()
{
	for (const auto& Racer : Racers)
	{
		RequestToAssignRacersToRace(Racer);
	}
}


void UGP_Rules::MakeRandomRosters()
{
	if (Racers.IsEmpty()) return;
	TArray<int32> UsedRacerNumbers;
	for (const auto& Racer : Racers)
	{
		int32 RacerNumber = 0;
		RacerNumber = FMath::RandRange(1, Racers.Num());
		if (UsedRacerNumbers.Contains(RacerNumber))
		{
			while (UsedRacerNumbers.Contains(RacerNumber))
			{
				RacerNumber = FMath::RandRange(1, Racers.Num());
			}
		}
		UsedRacerNumbers.Add(RacerNumber);
		Racer->SetRacerNumber(RacerNumber);
	}
}


void UGP_Rules::SortRacers()
{
	Racers.Sort([](URacerMatchManager& L1, URacerMatchManager& L2)
	{
		if (L1.CountOverallPoints() != L2.CountOverallPoints())
		{
			return L1.CountOverallPoints() > L2.CountOverallPoints();
		}
		if (L1.GetAmountOfWins() != L2.GetAmountOfWins())
		{
			return L1.GetAmountOfWins() > L2.GetAmountOfWins();
		}
		if (L1.GetDefeatedRivals().Contains(L2.GetRacerNumber())) return true;
		if (L2.GetDefeatedRivals().Contains(L1.GetRacerNumber())) return false;
		
		if (L1.GetAmountOfUnfinishedRaces() != L2.GetAmountOfUnfinishedRaces())
		{
			return L1.GetAmountOfUnfinishedRaces() < L2.GetAmountOfUnfinishedRaces();
		}
		return false;
	});
}


void UGP_Rules::HandleRaceFinished()
{
	Races[CurrentRace].RaceManager->OnChangedRaceStatusDelegate.Broadcast(false);
	if (!Races[CurrentRace].RaceManager->IsNominatedRace() && Races[CurrentRace+1].RaceManager->IsNominatedRace())
	{
		SortRacers();
	}
	CurrentRace++;
	if (CurrentRace <= Races.Num())
	{
		Races[CurrentRace].RaceManager->OnChangedRaceStatusDelegate.Broadcast(true);
		bool IsNominatedRace = Races[CurrentRace].RaceManager->IsNominatedRace();
		if (IsNominatedRace)
		{
			if (Races[CurrentRace].RaceManager->GetRaceID() == 21)
			{
				SetNominatedRaceLines(Semifinal1Racers);
				FillNominatedRaceLines(Semifinal1Racers);
			}
			if (Races[CurrentRace].RaceManager->GetRaceID() == 22)
			{
				SetNominatedRaceLines(Semifinal2Racers);
				FillNominatedRaceLines(Semifinal2Racers);
			}
			if (Races[CurrentRace].RaceManager->GetRaceID() == 23)
			{
				SetFinalRace();
				FillFinalRace();
			}
		}
		Races[CurrentRace].RaceLineupManager->OnHandleRaceLinesRequestDelegate.Broadcast(IsNominatedRace);
	}
	else OnRacingFinishedDelegate.Broadcast();
}


void UGP_Rules::SetNominatedRaceLines(const TArray<int32>& RacersNumbers)
{
	TArray<TObjectPtr<URacerMatchManager>> MatchManagers;
	for (int32 Position = 0; Position < Racers.Num() / 2; Position++)
	{
		if (RacersNumbers.Contains(Position)) MatchManagers.Add(Racers[Position]);
	}
	int32 Position = 0;
	for (const auto& RaceLine : Races[CurrentRace].RaceLineupManager->RaceLines)
	{
		RaceLine->SetRacerNumber(MatchManagers[Position]->GetRacerNumber());
		Position++;
	}
}


void UGP_Rules::FillNominatedRaceLines(const TArray<int32>& RacersNumbers)
{
	for (int32 Position = 0; Position < Racers.Num() / 2; Position++)
	{
		if (RacersNumbers.Contains(Position))
		{
			RequestToAssignRacersToCertainRace(Racers[Position], Races[CurrentRace].RaceManager->GetRaceID());
		}
	}
}


void UGP_Rules::SetFinalRace()
{
	int32 Position = 0;
	for (const auto& RaceLine : Races[CurrentRace].RaceLineupManager->RaceLines)
	{
		RaceLine->SetRacerNumber(FinalQualifiedRacers[Position].RacerManager->GetRacerNumber());
		Position++;
	}
}


void UGP_Rules::FillFinalRace()
{
	int32 CurrentRaceID = Races[CurrentRace].RaceManager->GetRaceID();
	for (const auto& Racer : FinalQualifiedRacers)
	{
		RequestToAssignRacersToCertainRace(Racer.RacerManager, CurrentRaceID);
	}
}


void UGP_Rules::RequestToAssignRacersToCertainRace(URacerMatchManager* RacerManager, int32 RaceID)
{
	if (Races.Contains(RaceID))
	{
		Races[RaceID].RaceLineupManager->AssignRacerToRace(RacerManager);
	}
}


void UGP_Rules::HandleLineup()
{
	ASMS_GameMode* GameMode = Cast<ASMS_GameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	UE_LOG(LogTemp, Warning, TEXT("Creating racers"));
	for (const auto& Racer : GameMode->GetTopRacers())
	{
		if (URacerMatchManager* RacerMatchManager = NewObject<URacerMatchManager>(this))
		{
			RacerMatchManager->Initialize(Racer->GetRacerData());
			Racers.Add(RacerMatchManager);
		}
	}
}


void UGP_Rules::CollectRacerStatistics()
{
	UE_LOG(LogTemp, Warning, TEXT("CollectRacerStatistics"));
}


void UGP_Rules::PrepareToEndMatch()
{
	UE_LOG(LogTemp, Warning, TEXT("PrepareToEndMatch"));
}


void UGP_Rules::HandleMatchClosed()
{
	UE_LOG(LogTemp, Warning, TEXT("HandleMatchClosed"));
}


bool UGP_Rules::CanStartMatch() const
{
	if (Racers.IsEmpty()) return false;
	return true;
}


#pragma once

#include "CoreMinimal.h"
#include "Data/RacersData/RacerMatchData.h"
#include "Data/RacersData/RacerStatistics.h"
#include "RacerMatchManager.generated.h"


class URaceLine_Base;
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPointsAdded, const ERaceResults&, bool)

UCLASS()
class SMS_API URacerMatchManager : public UObject
{
	GENERATED_BODY()

public:

	void Initialize(const FRacerData& RacerData);

	int32 CountOverallPoints();

	void CollectMatchStatistics();
	
	void AddPoints(const ERaceResults NewResult, bool AddBonus);
	
	void CalculateRating(float GateModifier, float DrivingModifier, ETrackTypes TrackType);

	int32 GetTieBreaker() const {return TieBreakerValue;}
	void SetTieBreaker() {TieBreakerValue = FMath::RandRange(1,100);}
	
	float GetCurrentRaceRating() const {return CurrentRacerRating;}
	
	int32 GetBonusAmount() const {return RacerBonuses;}

	int32 GetParticipatedRacesAmount() const {return ParticipatedRaces.Num();}
	
	void AddParticipatedRace(int32 RaceID, int32 RaceLineID);
	
	void RemoveParticipatedRace(int32 RaceID);

	int32 GetRacerAge() const {return Data.GetRacerAge();}
	
	FString& GetRacerName() {return Data.GetRacerName();}

	bool IsVisitor() const {return Data.IsVisitor();}

	int32 GetRacerNumber() const {return Data.RacerNumber;}
	void SetRacerNumber(int32 NewRacerNumber) {Data.RacerNumber = NewRacerNumber;}
	
	bool CanDriveMore(int32 MaxAmountOfRaces) const {return ParticipatedRaces.Num() < MaxAmountOfRaces;}
	
	bool DidParticipateInNominatedRace() const {return bParticipatedInNominatedRace;}
	void SetParticipatedInNominatedRace(bool NewParticipated) {bParticipatedInNominatedRace = NewParticipated;}

	void IncreaseAmountOfReplacements() {AmountOfReplacements++;}
	void DecreaseAmountOfReplacements() {AmountOfReplacements--;}
	int32 GetAmountOfReplacements() const {return AmountOfReplacements;}

	const ERaceResults& GetLastRaceResult() {return RacerPoints.Last();}

	int32 GetAmountOfWins() const;

	int32 GetAmountOfUnfinishedRaces() const;
	
	void AddDefeatedRival(int32 DefeatedRivalID) {DefeatedRivals.Add(DefeatedRivalID);}
	TArray<int32>& GetDefeatedRivals() {return DefeatedRivals;}
	
	FOnPointsAdded OnPointsAddedDelegate;
	
private:
	
	UPROPERTY()
	TMap<int32, int32> ParticipatedRaces;

	UPROPERTY()
	FRacerMatchData Data;

	UPROPERTY()
	TArray<ERaceResults> RacerPoints;

	UPROPERTY()
	TArray<int32> DefeatedRivals;
	
	int32 TieBreakerValue = 0;

	float CurrentRacerRating = 0.f;
	
	int32 RacerBonuses;

	int32 AmountOfReplacements = 0;
	
	bool bParticipatedInNominatedRace = false;
};
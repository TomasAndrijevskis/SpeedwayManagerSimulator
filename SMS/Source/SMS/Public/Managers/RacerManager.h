
#pragma once

#include "CoreMinimal.h"
#include "Data/RacersData/RacerMatchData.h"
#include "Data/RacersData/RacerStatistics.h"
#include "RacerManager.generated.h"

class URaceLineBase;
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPointsAdded, const ERaceResults&, bool)

UCLASS()
class SMS_API URacerManager : public UObject
{
	GENERATED_BODY()

public:

	void Initialize(const FRacerMatchData& RacerData);

	int32 CountOverallPoints();
	
	void AddPoints(const ERaceResults NewResult, bool AddBonus);
	
	void CalculateRating(bool IsVisitor, float GateModifier, float DrivingModifier);

	void SetTieBreaker();

	int32 GetTieBreaker() const;

	float GetCurrentRaceRating() const;
	
	int32 GetBonusAmount() const;

	int32 GetParticipatedRacesAmount() const;
	
	void AddParticipatedRace(URaceLineBase* RaceLineRef);

	void RemoveParticipatedRace(URaceLineBase* RaceLineRef);

	void OnRaceStarted(float GateModifier, float DistanceModifier);

	int32 GetRacerAge() const;
	
	FString GetRacerName() const;

	bool IsVisitor() const;

	int32 GetRacerNumber() const;

	bool CanDriveMore(int32 MaxAmountOfRaces) const;
	
	bool DidParticipateInNominatedRace() const;
	void SetParticipatedInNominatedRace(bool NewParticipated);

	void IncreaseAmountOfReplacements();
	void DecreaseAmountOfReplacements();
	int32 GetAmountOfReplacements() const;
	
	FOnPointsAdded OnPointsAddedDelegate;

	void CollectMatchStatistics();
	
private:

	UPROPERTY()
	TArray<ERaceResults> RacerPoints;
	
	UPROPERTY()
	TArray<URaceLineBase*> ParticipatedRacesRef;
	
	FRacerMatchData Data;

	int32 TieBreakerValue = 0;

	float CurrentRacerRating = 0.f;
	
	int32 RacerBonuses;

	int32 AmountOfReplacements = 0;
	
	bool bParticipatedInNominatedRace = false;
};
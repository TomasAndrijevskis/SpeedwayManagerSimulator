
#pragma once

#include "CoreMinimal.h"
#include "Data/RacersData/RacerMatchData.h"
#include "RacerManager.generated.h"

class URaceLineBase;
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPointsAdded, const FString&, bool)

UCLASS()
class SMS_API URacerManager : public UObject
{
	GENERATED_BODY()

public:

	void Initialize(const FRacerMatchData& RacerData);

	int CountOverallPoints();

	void AddPoints(const FString& NewPoints, bool AddBonus);
	
	void CalculateRating(bool IsVisitor);

	void SetTieBreaker();

	int GetTieBreaker() const;

	int GetCurrentRaceRating() const;
	
	int GetBonusAmount() const;

	int GetParticipatedRacesAmount() const;
	
	void AddParticipatedRace(URaceLineBase* RaceLineRef);

	void RemoveParticipatedRace(URaceLineBase* RaceLineRef);

	void OnRaceStarted();

	int GetRacerAge() const;
	
	FString GetRacerName() const;

	bool IsVisitor() const;

	int GetRacerNumber() const;

	bool CanDriveMore(int MaxAmountOfRaces) const;
	
	bool DidParticipateInNominatedRace() const;
	void SetParticipatedInNominatedRace(bool NewParticipated);
	
	FOnPointsAdded OnPointsAddedDelegate;
	
private:

	UPROPERTY()
	TArray<FString> RacerPoints;

	UPROPERTY()
	TArray<URaceLineBase*> ParticipatedRacesRef;
	
	FRacerMatchData Data;

	int TieBreakerValue = 0;

	int CurrentRacerRating = 0;
	
	int RacerBonuses;

	bool bParticipatedInNominatedRace = false;
};

#pragma once

#include "CoreMinimal.h"
#include "Data/RacersData/RacerMatchData.h"
#include "RacerManager.generated.h"

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

	FOnPointsAdded OnPointsAddedDelegate;

	void IncreaseRaceAmount();

	bool CanReplace() const;
	
private:

	bool CanAddNewPointBox() const;

	//Number during match 1-6 / 7-12
	int RacerNumber;
	
	FRacerMatchData Data;

	int MaxRacesAmount = 7;

	int TieBreakerValue = 0;

	int CurrentRacerRating = 0;

	int RaceAmount = 0;
	
	UPROPERTY(VisibleAnywhere)
	TArray<FString> RacerPoints;
};
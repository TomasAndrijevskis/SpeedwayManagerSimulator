
#pragma once

#include "CoreMinimal.h"
#include "Data/RacersData/RacerMatchData.h"
#include "RacerManager.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPointsAdded, const FString&)
UCLASS()
class SMS_API URacerManager : public UObject
{
	GENERATED_BODY()

public:

	void Initialize(const FRacerMatchData& RacerData);

	int CountOverallPoints(bool CanCount);

	void AddPoints(const FString& NewPoints);

	bool IsVisitor() const;
	
	void CalculateRating();

	void SetTieBreaker();

	int GetTieBreaker() const;

	int GetCurrentRaceRating() const;

	FOnPointsAdded OnPointsAddedDelegate;
	
private:

	bool CanAddNewPointBox() const;

	//Number during match 1-6 / 7-12
	int RacerNumber;
	
	FRacerMatchData Data;

	int MaxRacesAmount = 7;

	int TieBreakerValue = 0;

	int CurrentRacerRating = 0;
	
	UPROPERTY(VisibleAnywhere)
	TArray<FString> RacerPoints;
	
};

#pragma once

#include "CoreMinimal.h"
#include "Data/RacersData/RacerData.h"
#include "RacerManager.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnValueAddRequest, const FString&)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPointsAdded, const FString&)
UCLASS()
class SMS_API URacerManager : public UObject
{
	GENERATED_BODY()

public:

	void Init(int NewRacerNumber, const FRacerData& RacerData);

	int CountOverallPoints(bool CanCount);

	void AddPoints(const FString& NewPoints);

	FOnValueAddRequest OnValueAddRequestDelegate;

	FOnPointsAdded OnPointsAddedDelegate;
	
private:

	bool CanAddNewPointBox() const;
	
	int RacerNumber;
	
	FRacerData Data;

	int MaxRacesAmount = 7;
	
	UPROPERTY(VisibleAnywhere)
	TArray<FString> RacerPoints;
	
};

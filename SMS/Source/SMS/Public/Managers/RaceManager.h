
#pragma once

#include "CoreMinimal.h"
#include "UI/League/Program/RaceLine.h"
#include "RaceManager.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnOverallScoreUpdated, int, int);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRaceFinished, int, int);
UCLASS()
class SMS_API URaceManager : public UObject
{
	GENERATED_BODY()

public:

	void SimulateRace();

	void AddRaceLine(URaceLine* NewRaceLine);
	
	TArray<URaceLine*> GetRaceLines();
	

	FOnRaceFinished OnRaceFinishedDelegate;

	FOnOverallScoreUpdated OnOverallScoreUpdatedDelegate;
	
private:

	void AssignRacerToRace(const FString& RacerName, int RacerID);
	
	void ChangeRaceStatus(bool bIsActive);

	void SortArray();

	void CalculateRaceResult();
	
	UPROPERTY()
	TArray<URaceLine*> RaceLines;
};

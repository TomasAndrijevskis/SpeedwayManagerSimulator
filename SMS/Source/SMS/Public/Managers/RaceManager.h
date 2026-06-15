
#pragma once

#include "CoreMinimal.h"
#include "UI/League/Program/RaceLine.h"
#include "RaceManager.generated.h"

//DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRaceFinished, int, int);
DECLARE_MULTICAST_DELEGATE(FOnRaceFinished);
UCLASS()
class SMS_API URaceManager : public UObject
{
	GENERATED_BODY()

public:

	void SimulateRace();

	void AddRaceLine(URaceLine* NewRaceLine);

	void AssignRacerToRace(const FString& RacerName, int RacerID);
	
	void ChangeRaceStatus(bool bIsActive);
	
	TArray<URaceLine*> GetRaceLines();

	void CalculateRaceResult(int& HomePts, int& VisitorPts);
	
	FOnRaceFinished OnRaceFinishedDelegate;
	
private:
	
	void SortArray();
	
	UPROPERTY()
	TArray<URaceLine*> RaceLines;
};

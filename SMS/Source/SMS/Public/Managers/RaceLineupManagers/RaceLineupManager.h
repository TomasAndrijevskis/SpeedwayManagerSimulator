
#pragma once

#include "CoreMinimal.h"
#include "RaceLineupManager.generated.h"

class URaceLine_Base;
class UTeamManager;
class URacerMatchManager;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnHandleRaceLines, bool);
UCLASS()
class SMS_API URaceLineupManager : public UObject
{
	GENERATED_BODY()

public:

	void InitializeManager();

	void AddRaceLine(URaceLine_Base* NewRaceLine);

	void AssignRacerToRace(URacerMatchManager* RacerManager);

	TArray<TObjectPtr<URaceLine_Base>>& GetRaceLines() {return RaceLines;}
	
	FOnHandleRaceLines OnHandleRaceLinesDelegate;
	
protected:

	virtual void BindDelegates() {};
	
	UPROPERTY()
	TArray<TObjectPtr<URaceLine_Base>> RaceLines;
	
private:
	
};


#pragma once

#include "CoreMinimal.h"
#include "Managers/RaceManagers/RaceManager_Base.h"
#include "League_RaceManager.generated.h"


UCLASS()
class SMS_API ULeague_RaceManager : public URaceManager_Base
{
	GENERATED_BODY()

public:

	void RemoveRacerManager(int32 RaceLineID);
	
private:

	virtual void SimulateRace() override;

	void BroadcastRaceResult(TArray<FRaceResultData>& ResultForEachLine) const;

	bool AreRacersFromSameTeam(int32 Position, const TObjectPtr<URacerMatchManager>& PreviousManager, bool IsCurrentRacerVisitor);
	
	void CollectRaceLineData(ERaceResults Result, int32 RacerNumber, const UCompetitionRules& Rules, TArray<FRaceResultData>& OutArray);
	
};

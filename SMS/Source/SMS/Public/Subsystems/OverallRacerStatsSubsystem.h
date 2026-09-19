

#pragma once

#include "CoreMinimal.h"
#include "Data/RacersData/RacerStatistics.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "OverallRacerStatsSubsystem.generated.h"

UCLASS()
class SMS_API UOverallStatsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	void AddStat(const FRacerStatistics& CurrentMatchStatistics);

	TArray<FRacerStatistics>& GetRacerStatistics() {return RacerStatistics;}
	
private:

	UPROPERTY()
	TArray<FRacerStatistics> RacerStatistics;
	
};

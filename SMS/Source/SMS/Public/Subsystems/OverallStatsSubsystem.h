

#pragma once

#include "CoreMinimal.h"
#include "Data/RacersData/RacerStatistics.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "OverallStatsSubsystem.generated.h"

UCLASS()
class SMS_API UOverallStatsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	void AddStat(const FRacerStatistics& CurrentMatchStatistics);

	TArray<FRacerStatistics>& GetRacerStatistics();
	
private:

	TArray<FRacerStatistics> RacerStatistics;
	
};

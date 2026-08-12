
#pragma once

#include "CoreMinimal.h"
#include "Data/TeamData/TeamStatistics.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "StandingsSubsystem.generated.h"

UCLASS()
class SMS_API UStandingsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	void AddTeamStatistics(const FTeamStatistics& NewTeamStatistics);

	TArray<FTeamStatistics>& GetTeamStatistics();

private:

	TArray<FTeamStatistics> TeamStatistics;
	
};

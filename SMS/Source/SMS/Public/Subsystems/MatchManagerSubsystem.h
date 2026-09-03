
#pragma once

#include "CoreMinimal.h"
#include "Rules/CompetitionRules.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MatchManagerSubsystem.generated.h"


UCLASS()
class SMS_API UMatchManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	void StartMatch(TSubclassOf<UCompetitionRules> RulesType);

	UCompetitionRules* GetCompetitionRules() const;
	
private:

	UPROPERTY()
	UCompetitionRules* CurrentRules;
};

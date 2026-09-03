
#include "Subsystems/MatchManagerSubsystem.h"


void UMatchManagerSubsystem::StartMatch(TSubclassOf<UCompetitionRules> RulesType)
{
	CurrentRules = NewObject<UCompetitionRules>(this, RulesType);
	if (CurrentRules) CurrentRules->SetupMatch();
}


UCompetitionRules* UMatchManagerSubsystem::GetCompetitionRules() const
{
	return CurrentRules;
}

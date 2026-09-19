
#include "Subsystems/MatchManagerSubsystem.h"


void UMatchManagerSubsystem::StartMatch(TSubclassOf<UCompetitionRules> RulesType)
{
	if (CurrentRules) ClearRules();
	CurrentRules = NewObject<UCompetitionRules>(this, RulesType);
	if (CurrentRules)
	{
		CurrentRules->SetupMatch();
	}
}


void UMatchManagerSubsystem::ClearRules()
{
	CurrentRules = nullptr;
}


UCompetitionRules* UMatchManagerSubsystem::GetCompetitionRules() const
{
	return CurrentRules;
}
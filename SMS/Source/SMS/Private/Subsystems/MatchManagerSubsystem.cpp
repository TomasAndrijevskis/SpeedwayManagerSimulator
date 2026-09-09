
#include "Subsystems/MatchManagerSubsystem.h"


void UMatchManagerSubsystem::StartMatch(TSubclassOf<UCompetitionRules> RulesType)
{
	CurrentRules = NewObject<UCompetitionRules>(this, RulesType);
	if (CurrentRules)
	{
		CurrentRules->SetupMatch();
		CurrentRules->OnMatchClosedDelegate.AddUObject(this, &UMatchManagerSubsystem::ClearDependencies);
	}
}


void UMatchManagerSubsystem::ClearDependencies()
{
	CurrentRules->OnMatchClosedDelegate.Clear();
	CurrentRules = nullptr;
}


UCompetitionRules* UMatchManagerSubsystem::GetCompetitionRules() const
{
	return CurrentRules;
}
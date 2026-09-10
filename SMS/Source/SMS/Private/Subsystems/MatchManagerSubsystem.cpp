
#include "Subsystems/MatchManagerSubsystem.h"


void UMatchManagerSubsystem::StartMatch(TSubclassOf<UCompetitionRules> RulesType)
{
	CurrentRules = NewObject<UCompetitionRules>(this, RulesType);
	if (CurrentRules)
	{
		CurrentRules->SetupMatch();
		CurrentRules->OnMatchClosedDelegate.AddUObject(this, &UMatchManagerSubsystem::ClearRules);
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
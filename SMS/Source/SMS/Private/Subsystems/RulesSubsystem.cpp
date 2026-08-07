
#include "Subsystems/RulesSubsystem.h"
#include "Managers/RacerManager.h"


void URulesSubsystem::InitializeRules()
{
	Positions.Add(EPositionTypes::Senior);
	Positions.Add(EPositionTypes::Senior);
	Positions.Add(EPositionTypes::Senior);
	Positions.Add(EPositionTypes::Senior);
	Positions.Add(EPositionTypes::Junior);
	Positions.Add(EPositionTypes::Replacement);
	Positions.Add(EPositionTypes::Senior);
	Positions.Add(EPositionTypes::Senior);
	Positions.Add(EPositionTypes::Senior);
	Positions.Add(EPositionTypes::Senior);
	Positions.Add(EPositionTypes::Junior);
	Positions.Add(EPositionTypes::Replacement);
	ReplacementRules.Emplace(2, EPositionTypes::Junior);
	ReplacementRules.Emplace(1, EPositionTypes::Senior);
	ReplacementRules.Emplace(5, EPositionTypes::Replacement);
}


bool URulesSubsystem::IsRacerEligible(int32 RaceLineID, int32 Age) const
{
	if (Positions[RaceLineID - 1] == EPositionTypes::Junior) return IsJunior(Age);
	return true;
}


bool URulesSubsystem::CanReplace(const URacerManager* OriginalRacer, const URacerManager* ReplacementRacer, int32 OwnTeamScore, int32 EnemyTeamScore) const
{
	if (!OriginalRacer || !ReplacementRacer) return false;
	if (OriginalRacer == ReplacementRacer) return false;
	if (!ReplacementRacer->CanDriveMore(MaxAmountOfRaces)) return false;
	if (!CheckPossibleAmountOfReplacements(ReplacementRacer->GetAmountOfReplacements(), GetPositionType(ReplacementRacer->GetRacerNumber()))) return false;
	
	int32 originalRacerNumber = OriginalRacer->GetRacerNumber();
	int32 replaceRacerNumber = ReplacementRacer->GetRacerNumber();
	if (GetPositionType(originalRacerNumber) == EPositionTypes::Replacement) return false;
	if (IsTeamLosing(OwnTeamScore, EnemyTeamScore))
	{
		if (GetPositionType(originalRacerNumber) == EPositionTypes::Junior)
			return GetPositionType(replaceRacerNumber) == EPositionTypes::Replacement && IsJunior(ReplacementRacer->GetRacerAge());
		return true;
	}
	else
	{
		if (GetPositionType(originalRacerNumber) != EPositionTypes::Junior)
		{
			return GetPositionType(replaceRacerNumber) == EPositionTypes::Junior || GetPositionType(replaceRacerNumber) == EPositionTypes::Replacement;
		}
		if (GetPositionType(originalRacerNumber) == EPositionTypes::Junior)
		{
			if (GetPositionType(replaceRacerNumber) == EPositionTypes::Replacement)
			{
				return IsJunior(ReplacementRacer->GetRacerAge());
			}
			if (GetPositionType(replaceRacerNumber) != EPositionTypes::Junior) return false;
		}
	}
	return false;
}


bool URulesSubsystem::CanParticipateInNominatedRace(const URacerManager* RacerManagerRef) const
{
	return !RacerManagerRef->DidParticipateInNominatedRace() && RacerManagerRef->CanDriveMore(MaxAmountOfRaces);
}


bool URulesSubsystem::IsTeamLosing(int32 OwnTeamScore, int32 EnemyTeamScore) const
{
	return EnemyTeamScore >= OwnTeamScore + TeamScoreDifference;
}


bool URulesSubsystem::CheckPossibleAmountOfReplacements(int32 AmountOfReplacements, EPositionTypes Position) const
{
	for (const auto& Rule : ReplacementRules)
	{
		if (Rule.PositionType == Position) return Rule.MaxReplacements > AmountOfReplacements;
	}
	return false;
}


bool URulesSubsystem::IsJunior(int32 RacerAge) const{return RacerAge <= JuniorAge;}
EPositionTypes URulesSubsystem::GetPositionType(int32 RacerNumber) const {return Positions[RacerNumber - 1];}

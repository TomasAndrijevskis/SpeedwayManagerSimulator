
#include "Managers/RuleBook.h"
#include "Managers/RacerManager.h"
#include "Managers/ScoreManager.h"
#include "UI/League/Program/RacerStatsLine.h"


void URuleBook::InitializeRules(UScoreManager* Manager)
{
	ScoreManager = Manager;
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


bool URuleBook::IsRacerEligible(const URacerStatsLine* RacerStatsLineRef, int32 Age) const
{
	int32 ID = RacerStatsLineRef->GetID();
	if (Positions[ID] == Junior) return IsJunior(Age);
	return true;
}


bool URuleBook::CanReplace(const URacerManager* OriginalRacer, const URacerManager* ReplacementRacer) const
{
	if (!OriginalRacer || !ReplacementRacer) return false;
	if (OriginalRacer == ReplacementRacer) return false;
	if (!ReplacementRacer->CanDriveMore(MaxAmountOfRaces)) return false;
	//if (!CheckPossibleAmountOfReplacements(ReplacementRacer->GetAmountOfReplacements())) return false;
	
	int32 originalRacerNumber = OriginalRacer->GetRacerNumber();
	int32 replaceRacerNumber = ReplacementRacer->GetRacerNumber();
	if (GetPositionType(originalRacerNumber) == Replacement) return false;
	if (IsTeamLosing(OriginalRacer))
	{
		if (GetPositionType(originalRacerNumber) == Junior)
			return GetPositionType(replaceRacerNumber) == Replacement && IsJunior(ReplacementRacer->GetRacerAge());
		return true;
	}
	else
	{
		if (GetPositionType(originalRacerNumber) != Junior)
		{
			return GetPositionType(replaceRacerNumber) == Junior || GetPositionType(replaceRacerNumber) == Replacement;
		}
		if (GetPositionType(originalRacerNumber) == Junior)
		{
			if (GetPositionType(replaceRacerNumber) == Replacement)
			{
				return IsJunior(ReplacementRacer->GetRacerAge());
			}
			if (GetPositionType(replaceRacerNumber) != Junior) return false;
		}
	}
	return false;
}


bool URuleBook::CanParticipateInNominatedRace(const URacerManager* RacerManagerRef) const
{
	return !RacerManagerRef->DidParticipateInNominatedRace() && RacerManagerRef->CanDriveMore(MaxAmountOfRaces);
}


bool URuleBook::IsTeamLosing(const URacerManager* RacerManagerRef) const
{
	if (!ScoreManager || !RacerManagerRef) return false;
	const int32 OwnTeamScore = ScoreManager->GetTeamScore(RacerManagerRef->IsVisitor());
	const int32 EnemyTeamScore = ScoreManager->GetTeamScore(!RacerManagerRef->IsVisitor());
	return EnemyTeamScore >= OwnTeamScore + TeamScoreDifference;
}

/*
bool URuleBook::CheckPossibleAmountOfReplacements(int32 AmountOfReplacements) const
{
	return true;
}
*/

bool URuleBook::IsJunior(int32 RacerAge) const{return RacerAge <= JuniorAge;}
EPositionTypes URuleBook::GetPositionType(int32 RacerNumber) const {return Positions[RacerNumber];}
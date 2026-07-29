
#include "Managers/RuleBook.h"
#include "Managers/RacerManager.h"
#include "Managers/ScoreManager.h"
#include "UI/League/Program/RacerStatsLine.h"


void URuleBook::InitializeRules(UScoreManager* Manager)
{
	ScoreManager = Manager;
}


bool URuleBook::IsRacerEligible(const URacerStatsLine* RacerStatsLineRef, int32 Age) const
{
	int32 ID = RacerStatsLineRef->GetID();
	if (JuniorPositions.Contains(ID)) return IsJunior(Age);
	return true;
}


bool URuleBook::CanReplace(const URacerManager* OriginalRacer, const URacerManager* ReplacementRacer) const
{
	if (!OriginalRacer || !ReplacementRacer) return false;
	if (OriginalRacer == ReplacementRacer) return false;
	if (!ReplacementRacer->CanDriveMore(MaxAmountOfRaces)) return false;
	
	int originalRacerNumber = OriginalRacer->GetRacerNumber();
	int replaceRacerNumber = ReplacementRacer->GetRacerNumber();
	if (IsReplacement(originalRacerNumber)) return false;
	if (IsTeamLosing(OriginalRacer))
	{
		if (IsOnJuniorPosition(originalRacerNumber))
			return IsReplacement(replaceRacerNumber) && IsJunior(ReplacementRacer->GetRacerAge());
		return true;
	}
	else
	{
		if (!IsOnJuniorPosition(originalRacerNumber))
		{
			if (IsOnJuniorPosition(replaceRacerNumber) || IsReplacement(replaceRacerNumber)) return true;
			return false;
		}
		if (IsOnJuniorPosition(originalRacerNumber))
		{
			if (IsReplacement(replaceRacerNumber))
			{
				if (IsJunior(ReplacementRacer->GetRacerAge()))
				{
					return true;
				}
				return false;
			}
			if (!IsOnJuniorPosition(replaceRacerNumber)) return false;
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


bool URuleBook::IsJunior(int32 RacerAge) const{return RacerAge <= JuniorAge;}
bool URuleBook::IsOnJuniorPosition(int32 RacerNumber) const {return JuniorPositions.Contains(RacerNumber);}
bool URuleBook::IsReplacement(int32 RacerNumber) const {return ReplacementPositions.Contains(RacerNumber);}
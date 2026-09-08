
#include "Subsystems/RulesSubsystem.h"
#include "Managers/RacerMatchManager.h"
#include "Managers/TeamManager.h"


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


bool URulesSubsystem::CanReplace(const URacerMatchManager* OriginalRacer, const URacerMatchManager* ReplacementRacer, int32 OwnTeamScore, int32 EnemyTeamScore) const
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


bool URulesSubsystem::CanParticipateInNominatedRace(const URacerMatchManager* RacerManagerRef) const
{
	return !RacerManagerRef->DidParticipateInNominatedRace() && RacerManagerRef->CanDriveMore(MaxAmountOfRaces);
}


FString URulesSubsystem::GetRaceResultText(const ERaceResults RaceResult) const
{
	switch (RaceResult)
	{
		case ERaceResults::First:
			return FString::FromInt(3);
		case ERaceResults::Second:
			return FString::FromInt(2);
		case ERaceResults::Third:
			return FString::FromInt(1);
		case ERaceResults::Fourth:
			return FString::FromInt(0);
		case ERaceResults::Defect:
			return "D";
		default: return "DNF";
	}
}


int32 URulesSubsystem::GetRaceResultNumber(const ERaceResults RaceResult) const
{
	switch (RaceResult)
	{
	case ERaceResults::First:
		return 3;
	case ERaceResults::Second:
		return 2;
	case ERaceResults::Third:
		return 1;
	case ERaceResults::Fourth:
		return 0;
	default: return 0;
	}
}


void URulesSubsystem::DecideMatchWinner(const TObjectPtr<UTeamManager>& HomeTeamManager, const TObjectPtr<UTeamManager>& VisitorTeamManager)
{
	if (!VisitorTeamManager || !HomeTeamManager) return;
	TMap<ETeams, int32> VisitorTeamData;
	TMap<ETeams, int32> HomeTeamData;
	
	int32 HomeTeamScore = HomeTeamManager->GetTeamScore();
	int32 VisitorTeamScore = VisitorTeamManager->GetTeamScore();

	VisitorTeamData.Add(VisitorTeamManager->GetTeam(), VisitorTeamScore);
	HomeTeamData.Add(HomeTeamManager->GetTeam(), HomeTeamScore);
	
	if (HomeTeamScore > VisitorTeamScore)
	{
		HomeTeamManager->CollectTeamStatistics(EMatchResults::Win, VisitorTeamData);
		VisitorTeamManager->CollectTeamStatistics(EMatchResults::Loss, HomeTeamData);
		return;
	}
	if (HomeTeamScore < VisitorTeamScore)
	{
		HomeTeamManager->CollectTeamStatistics(EMatchResults::Loss, VisitorTeamData);
		VisitorTeamManager->CollectTeamStatistics(EMatchResults::Win,  HomeTeamData);
		return;
	}
	HomeTeamManager->CollectTeamStatistics(EMatchResults::Draw, VisitorTeamData);
	VisitorTeamManager->CollectTeamStatistics(EMatchResults::Draw, HomeTeamData);
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

bool URulesSubsystem::IsTrackCleaningTime(int32 CurrentRace) const{return TrackCleaningRaces.Contains(CurrentRace);}
bool URulesSubsystem::IsJunior(int32 RacerAge) const{return RacerAge <= JuniorAge;}
EPositionTypes URulesSubsystem::GetPositionType(int32 RacerNumber) const {return Positions[RacerNumber - 1];}

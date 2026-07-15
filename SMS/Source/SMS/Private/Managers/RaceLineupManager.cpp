
#include "Managers/RaceLineupManager.h"
#include "Gamemodes/SMS_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/ScoreManager.h"
#include "UI/League/Program/RaceLineBase.h"


void URaceLineupManager::InitializeManager()
{
	ASMS_GameMode* GameMode = Cast<ASMS_GameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	ScoreManager = GameMode->GetScoreManager();
	BindRaceLineDelegates();
}


void URaceLineupManager::SetRaceLines(const TArray<URaceLineBase*>& NewRaceLines)
{
	RaceLines = NewRaceLines;
}


void URaceLineupManager::BindRaceLineDelegates()
{
	for (const auto& RaceLine : RaceLines)
	{
		RaceLine->OnRacerReplacedDelegate.AddUObject(this, &URaceLineupManager::OnRacerReplaced);
	}
}


void URaceLineupManager::OnRacerReplaced(const URaceLineBase* RaceLineRef, const FString& RacerName)
{
	for (auto& RaceLine : RaceLines)
	{
		if (RaceLine != RaceLineRef) RaceLine->RemoveOption(RacerName);
	}
}


void URaceLineupManager::AssignRacerToRace(const FRacerMatchData& RacerData, URacerManager* RacerManagerRef)
{
	for (const auto& RaceLine : RaceLines)
	{
		if (RaceLine->GetRacerNumber() == RacerData.RacerNumber) RaceLine->SetRacerData(RacerData.GetRacerName(), RacerManagerRef);
	}
}


bool URaceLineupManager::IsTeamLosing(const URaceLineBase* RaceLineRef) const
{
	if (!ScoreManager) return false;
	const int OwnTeamScore = ScoreManager->GetTeamScore(RaceLineRef->IsVisitor());
	const int EnemyTeamScore = ScoreManager->GetTeamScore(!RaceLineRef->IsVisitor());
	return EnemyTeamScore >= OwnTeamScore + 6;
}

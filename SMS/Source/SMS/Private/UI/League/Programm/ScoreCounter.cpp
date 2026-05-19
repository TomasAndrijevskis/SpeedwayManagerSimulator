
#include "UI/League/Programm/ScoreCounter.h"

#include "Gamemodes/SMS_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/PointsManager.h"
#include "UI/BaseClasses/NumbersBox.h"


void UScoreCounter::NativeConstruct()
{
	Super::NativeConstruct();
	ASMS_GameMode* GameMode = Cast<ASMS_GameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	PointsManager = GameMode->GetPointsManager();
	if (!PointsManager) return;
	PointsManager->OnScoreChangedDelegate.AddUObject(this, &UScoreCounter::SetOverallScore);
}


void UScoreCounter::SetRacePoints(int NewHomePoints, int NewVisitorPoints)
{
	NumbersBox_HomeTeamRacePoints->SetText(NewHomePoints);
	NumbersBox_VisitorTeamRacePoints->SetText(NewVisitorPoints);
	PointsManager->UpdateOverallScore(NewHomePoints, NewVisitorPoints);
}


void UScoreCounter::SetOverallScore(int NewHomePoints, int NewVisitorPoints)
{
	NumbersBox_HomeTeamOverallPoints->SetText(NewHomePoints);
	NumbersBox_VisitorTeamOverallPoints->SetText(NewVisitorPoints);
}

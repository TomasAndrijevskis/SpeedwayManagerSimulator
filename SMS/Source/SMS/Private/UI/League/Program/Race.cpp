
#include "SMS/Public/UI/League/Program/Race.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Data/RaceData/RacePatternsDataAsset.h"
#include "Gamemodes/SMS_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/RaceManager.h"
#include "Managers/ScoreManager.h"
#include "UI/BaseClasses/NumbersBox.h"
#include "SMS/Public/UI/League/Program/RaceLine.h"
#include "SMS/Public/UI/League/Program/ScoreCounter.h"
#include "UI/League/Program/NominatedRaceLine.h"


void URace::InitializeWidget(int NewID)
{
	RaceID = NewID;
	NumbersBox_RaceNumber->SetText(RaceID);
	InitializeManagers();
	BindDelegates();
	OnIDSet();
}


void URace::OnIDSet()
{
	CreateRaceLines();
	if (RaceID != 1) RaceManager->ChangeRaceStatus(false);
}


void URace::InitializeManagers()
{
	ASMS_GameMode* GameMode = Cast<ASMS_GameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	ScoreManager = GameMode->GetScoreManager();
	RaceManager = NewObject<URaceManager>(this);
	if (!RaceManager || !ScoreManager) return;
	RaceManager->BindDelegates();
}


void URace::BindDelegates()
{
	if (!RaceManager || !ScoreManager) return;
	RaceManager->OnRaceFinishedDelegate.AddUObject(this, &URace::UpdateRacePoints);
	RaceManager->OnRaceFinishedDelegate.AddUObject(this, &URace::UpdateOverallScore);
}


void URace::CreateRaceLines()
{
	if (!RaceManager || !RaceDataAsset) return;
	const int RaceLineAmount = RaceDataAsset->RacePatterns[RaceID].RaceLines.Num();
	for (int RaceLineID = 0; RaceLineID < RaceLineAmount; RaceLineID++)
	{
		URaceLineBase* NewRaceLine;
		if (!IsNominatedRace()) NewRaceLine = CreateRaceLine(RaceLineID);
		else  NewRaceLine = CreateNominatedRaceLine(RaceLineID);
		if (NewRaceLine)
		{
			UVerticalBoxSlot* VB_Slot = VB_Content->AddChildToVerticalBox(NewRaceLine);
			if (VB_Slot)
			{
				VB_Slot->SetHorizontalAlignment(HAlign_Fill);
				VB_Slot->SetVerticalAlignment(VAlign_Fill);
			}
			
			NewRaceLine->SetRaceLineData(GetRaceLineData(RaceLineID));
			RaceManager->AddRaceLine(NewRaceLine);
		}
	}
}


URaceLineBase* URace::CreateRaceLine(int RaceLineID)
{
	if (!RaceLineClass) return nullptr;
	URaceLine* NewRaceLine = CreateWidget<URaceLine>(this, RaceLineClass);
	if (!NewRaceLine) return nullptr;
	NewRaceLine->SetRaceLineID(RaceLineID);
	return NewRaceLine;
}


URaceLineBase* URace::CreateNominatedRaceLine(int RaceLineID)
{
	if (!NominatedRaceLineClass) return nullptr;
	UNominatedRaceLine* NewRaceLine = CreateWidget<UNominatedRaceLine>(this, NominatedRaceLineClass);
	if (!NewRaceLine) return nullptr;
	NewRaceLine->SetRaceLineID(RaceLineID);
	return NewRaceLine;
}


void URace::UpdateRacePoints()
{
	if (!ScoreManager) return;
	ScoreCounter->SetRacePoints(
		ScoreManager->GetRaceScore(false),
		ScoreManager->GetRaceScore(true));
}


void URace::UpdateOverallScore()
{
	if (!ScoreManager) return;
	ScoreCounter->SetOverallScore(
		ScoreManager->GetTeamScore(false),
		ScoreManager->GetTeamScore(true));
}


URaceManager* URace::GetRaceManager() const{return RaceManager;}
FRaceLineData& URace::GetRaceLineData(int RaceLineId) const{return RaceDataAsset->RacePatterns[RaceID].RaceLines[RaceLineId];}
bool URace::IsNominatedRace() const{return RaceDataAsset->RacePatterns[RaceID].IsNominatedRace;}

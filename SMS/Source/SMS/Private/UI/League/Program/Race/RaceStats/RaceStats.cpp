
#include "UI/League/Program/Race/RaceStats/RaceStats.h"
#include "Components/HorizontalBox.h"
#include "Managers/RaceStatsManager.h"
#include "UI/League/Program/Race/RaceStats/RaceLineStat.h"


void URaceStats::InitializeWidget()
{
	InitializeManager();
	CreateRaceLineStats();
}


void URaceStats::InitializeManager()
{
	RaceStatsManager = NewObject<URaceStatsManager>(this);
}


void URaceStats::UpdateStats(const TArray<FRaceResultData>& RaceResultData) const
{
	if (!HorizontalBox_Content->HasAnyChildren() || !RaceStatsManager) return;
	RaceStatsManager->HandleStatUpdate(RaceResultData);
}


void URaceStats::CreateRaceLineStats()
{
	if (!RaceStatsManager) return;
	for (int32 i = 0; i < RaceLineStatsAmount; i++)
	{
		URaceLineStat* NewRaceLineStat = CreateRaceLineStat(i);
		if (!NewRaceLineStat) return;
		HorizontalBox_Content->AddChild(NewRaceLineStat);
		RaceStatsManager->AddRaceLineStat(NewRaceLineStat);
	}
}


URaceLineStat* URaceStats::CreateRaceLineStat(int32 ID)
{
	if (!RaceLineStatClass) return nullptr;
	URaceLineStat* NewRaceLineStat = Cast<URaceLineStat>(CreateWidget(this, RaceLineStatClass));
	if (!NewRaceLineStat) return nullptr;
	NewRaceLineStat->SetID(ID);
	return NewRaceLineStat;
}
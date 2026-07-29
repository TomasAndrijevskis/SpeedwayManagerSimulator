
#include "UI/League/Program/Race/RaceStats/RaceStats.h"
#include "Components/HorizontalBox.h"
#include "UI/League/Program/Race/RaceStats/RaceLineStat.h"


void URaceStats::InitializeWidget()
{
	CreateRaceLineStats();
}

void URaceStats::NativeConstruct()
{
	Super::NativeConstruct();
	InitializeWidget();
}


void URaceStats::CreateRaceLineStats()
{
	for (int32 i = 0; i < RaceLineStatsAmount; i++)
	{
		URaceLineStat* NewRaceLineStat = CreateRaceLineStat(i);
		if (!NewRaceLineStat) return;
		HorizontalBox_Content->AddChild(NewRaceLineStat);
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

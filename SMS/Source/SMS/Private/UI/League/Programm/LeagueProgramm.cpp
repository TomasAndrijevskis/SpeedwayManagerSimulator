
#include "UI/League/Programm/LeagueProgramm.h"
#include "Components/Button.h"
#include "UI/League/Programm/Race.h"
#include "UI/League/Programm/RacerStatsLine.h"
#include "UI/League/Programm/TeamLineup.h"


void ULeagueProgramm::NativeConstruct()
{
	Super::NativeConstruct();
	Button_SimulateRace->OnClicked.AddUniqueDynamic(this, &ULeagueProgramm::SimulateRace);

	Races.Add(Race_First);
	Races.Add(Race_Second);
	Races.Add(Race_Third);
	for (const auto& Racer : TeamLineup_HomeTeam->GetRacers())
	{
		Racer->OnRacerChosenDelegate.AddUObject(this, &ULeagueProgramm::FillRacers);
	}
	/*RacerStatsLine_First->OnRacerChosenDelegate.AddUObject(Race_First, &URace::FindAndSetRacer);
	RacerStatsLine_Second->OnRacerChosenDelegate.AddUObject(Race_First, &URace::FindAndSetRacer);
	RacerStatsLine_Third->OnRacerChosenDelegate.AddUObject(Race_First, &URace::FindAndSetRacer);
	RacerStatsLine_Fourth->OnRacerChosenDelegate.AddUObject(Race_First, &URace::FindAndSetRacer);*/
}


void ULeagueProgramm::FillRacers(FString Name, int Id)
{
	for (const auto& Race : Races)
	{
		Race->FindAndSetRacer(Name, Id);
	}
}


void ULeagueProgramm::SimulateRace()
{
	for (const auto& Race : Races)
	{
		Race->SimulateRace();
	}
}

#include "UI/League/Programm/LeagueProgramm.h"
#include "Components/Button.h"
#include "UI/League/Programm/Race.h"
#include "UI/League/Programm/RacerStatsLine.h"


void ULeagueProgramm::NativeConstruct()
{
	Super::NativeConstruct();
	Button_SimulateRace->OnClicked.AddUniqueDynamic(this, &ULeagueProgramm::SimulateRace);
	
	RacerStatsLine_First->OnRacerChosenDelegate.AddUObject(Race_First, &URace::FindAndSetRacer);
	RacerStatsLine_Second->OnRacerChosenDelegate.AddUObject(Race_First, &URace::FindAndSetRacer);
	RacerStatsLine_Third->OnRacerChosenDelegate.AddUObject(Race_First, &URace::FindAndSetRacer);
	RacerStatsLine_Fourth->OnRacerChosenDelegate.AddUObject(Race_First, &URace::FindAndSetRacer);
}


void ULeagueProgramm::SimulateRace()
{
	Race_First->SimulateRace();
}

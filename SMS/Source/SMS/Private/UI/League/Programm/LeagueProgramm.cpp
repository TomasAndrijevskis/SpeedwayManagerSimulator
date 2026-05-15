
#include "UI/League/Programm/LeagueProgramm.h"
#include "Components/Button.h"
#include "UI/League/Programm/Race.h"


void ULeagueProgramm::NativeConstruct()
{
	Super::NativeConstruct();
	Button_SimulateRace->OnClicked.AddUniqueDynamic(this, &ULeagueProgramm::SimulateRace);
}


void ULeagueProgramm::SimulateRace()
{
	Race_First->SimulateRace();
}

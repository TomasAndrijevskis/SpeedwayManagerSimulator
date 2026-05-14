
#include "UI/League/Programm/Race.h"
#include "UI/League/Programm/RaceLine.h"


void URace::NativeConstruct()
{
	Super::NativeConstruct();

	RaceLine_First->SetRider(FColor::Red, "Tomas", "11");
	RaceLine_Second->SetRider(FColor::White, "Marek", "3");
	RaceLine_Third->SetRider(FColor::Blue, "Edik", "7");
	RaceLine_Fourth->SetRider(FColor::Yellow, "Ivars", "10");
}

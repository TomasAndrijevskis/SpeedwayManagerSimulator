
#include "UI/League/Programm/Race.h"
#include "UI/League/Programm/RaceLine.h"


void URace::NativeConstruct()
{
	Super::NativeConstruct();

	RaceLine_First->SetRider(FColor::Red, "Tomas", "11");
	RaceLine_Second->SetRider(FColor::White, "Marek", "3");
	RaceLine_Third->SetRider(FColor::Blue, "Edik", "7");
	RaceLine_Fourth->SetRider(FColor::Yellow, "Ivars", "10");
	RaceLines.Add(RaceLine_First);
	RaceLines.Add(RaceLine_Second);
	RaceLines.Add(RaceLine_Third);
	RaceLines.Add(RaceLine_Fourth);
}


void URace::SimulateRace()
{
	SortArray();
	int Points = 0;
	for (const auto& RaceLine : RaceLines)
	{
		UE_LOG(LogTemp, Error, TEXT("Racer: %s"), *RaceLine->GetName());
		UE_LOG(LogTemp, Error, TEXT("Number: %i"), RaceLine->GetNumber());
		RaceLine->SetPoints(Points);
		Points++;
	}
}


void URace::SortArray()
{
	RaceLines.Sort([](URaceLine& L1, URaceLine& L2)
	{
		return L1.GetNumber() < L2.GetNumber();
	});
}
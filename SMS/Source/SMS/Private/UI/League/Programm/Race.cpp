
#include "UI/League/Programm/Race.h"

#include "UI/BaseClasses/NumbersBox.h"
#include "UI/League/Programm/RaceLine.h"


void URace::NativeConstruct()
{
	Super::NativeConstruct();
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
		UE_LOG(LogTemp, Error, TEXT("%s - %i"), *RaceLine->GetName(), RaceLine->GetNumber());
		RaceLine->SetPoints(Points);
		Points++;
	}
}


void URace::AssignRacerToRace(FString RacerName, int RacerID)
{
	for (const auto& RaceLine : RaceLines)
	{
		if (RaceLine->GetID() == RacerID)
		{
			RaceLine->SetRacerName(RacerName);
		}
	}
}


void URace::SortArray()
{
	RaceLines.Sort([](URaceLine& L1, URaceLine& L2)
	{
		return L1.GetNumber() < L2.GetNumber();
	});
}


void URace::SetRaceID(int NewID)
{
	ID = NewID;
	NumbersBox_RaceNumber->SetText(FString::FromInt(ID));
}
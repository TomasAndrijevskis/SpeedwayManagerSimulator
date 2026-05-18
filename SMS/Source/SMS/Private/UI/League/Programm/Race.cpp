
#include "UI/League/Programm/Race.h"
#include "Data/RaceDataAsset.h"
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


void URace::SetRaceID(int NewID)
{
	ID = NewID;
	NumbersBox_RaceNumber->SetText(FString::FromInt(ID));
	SetRaceLinesID();
}


void URace::SetRaceLinesID()
{
	int RaceLineID = 0;
	for (auto& RaceLine : RaceLines)
	{
		RaceLine->SetID(RaceLineID);
		RaceLineID++;
	}
	SetRaceData();
}


void URace::SetRaceData()
{
	if (!RaceDataAsset) return;
	for (auto& RaceLine : RaceLines)
	{
		RaceLine->SetRacerValues(
			RaceDataAsset->RacePatterns[ID].HelmetColors[RaceLine->GetID()],
			RaceDataAsset->RacePatterns[ID].RacerNumbers[RaceLine->GetID()]);
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


void URace::SimulateRace()
{
	SortArray();
	int Points = 0;
	for (const auto& RaceLine : RaceLines)
	{
		UE_LOG(LogTemp, Error, TEXT("%s - %i"), *RaceLine->GetName(), RaceLine->GetGeneratedNumber());
		RaceLine->SetPoints(Points);
		Points++;
	}
}


void URace::SortArray()
{
	RaceLines.Sort([](URaceLine& L1, URaceLine& L2)
	{
		return L1.GetGeneratedNumber() < L2.GetGeneratedNumber();
	});
}
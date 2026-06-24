
#include "UI/League/Program/NominatedRaceWidgets/NominatedRace.h"
#include "Components/VerticalBox.h"
#include "UI/BaseClasses/NumbersBox.h"
#include "UI/League/Program/NominatedRaceWidgets/NominatedRaceLine.h"


void UNominatedRace::InitializeWidget(int NewRaceID)
{
	SetRaceID(NewRaceID);
	CreateNominatedRaceLines();
}


void UNominatedRace::CreateNominatedRaceLines()
{
	for (int i = 0; i < 4; i++)
	{
		UNominatedRaceLine* NewNominatedRaceLine = CreateNominatedRaceLine();
		if (!NewNominatedRaceLine) return;
		VB_Content->AddChildToVerticalBox(NewNominatedRaceLine);
		//NewNominatedRaceLine->SetData();
	}
}


UNominatedRaceLine* UNominatedRace::CreateNominatedRaceLine()
{
	if (!NominatedRaceLineClass) return nullptr;
	UNominatedRaceLine* NewNominatedRaceLine = CreateWidget<UNominatedRaceLine>(this, NominatedRaceLineClass);
	if (!NewNominatedRaceLine) return nullptr;
	return NewNominatedRaceLine;
}


void UNominatedRace::SetRaceID(int NewID)
{
	RaceID = NewID;
	NumbersBox_RaceNumber->SetText(RaceID);
}

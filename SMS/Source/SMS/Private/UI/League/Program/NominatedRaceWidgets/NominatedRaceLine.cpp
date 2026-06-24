
#include "UI/League/Program/NominatedRaceWidgets/NominatedRaceLine.h"
#include "UI/BaseClasses/NumbersBox.h"


void UNominatedRaceLine::SetData(const FColor& NewHelmetColour, int NewRacerID)
{
	RacerID = NewRacerID;
	NumbersBox_RacerNumber->SetText(RacerID);
	NumbersBox_RacerNumber->SetColour(NewHelmetColour);
}

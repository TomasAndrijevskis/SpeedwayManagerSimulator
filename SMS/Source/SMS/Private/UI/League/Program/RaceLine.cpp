
#include "SMS/Public/UI/League/Program/RaceLine.h"
#include "UI/BaseClasses/NamesBox.h"


void URaceLine::SetRacerName(const FString& NewRacerName)
{
	NamesBox_RacerName->SetText(NewRacerName);
}
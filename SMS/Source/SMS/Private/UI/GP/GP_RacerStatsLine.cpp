
#include "UI/GP/GP_RacerStatsLine.h"
#include "UI/BaseClasses/NamesBox.h"
#include "UI/BaseClasses/NumbersBox.h"


void UGP_RacerStatsLine::SetRacerName(const FString& Name)
{
	NamesBox_RacerName->SetText(Name);
}

void UGP_RacerStatsLine::UpdateRacerPosition(int32 NewPosition)
{
	NumbersBox_RacerPosition->SetText(NewPosition + 1);
}

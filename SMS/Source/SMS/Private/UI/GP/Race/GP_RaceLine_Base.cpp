
#include "UI/GP/Program/Race/GP_RaceLine_Base.h"
#include "UI/BaseClasses/NamesBox.h"


void UGP_RaceLine_Base::SetRacerName(const FString& NewRacerName)
{
	NamesBox_RacerName->SetText(NewRacerName);
}

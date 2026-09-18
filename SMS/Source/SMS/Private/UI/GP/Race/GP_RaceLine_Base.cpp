
#include "UI/GP/Program/Race/GP_RaceLine_Base.h"
#include "Managers/RacerMatchManager.h"
#include "UI/BaseClasses/NamesBox.h"


void UGP_RaceLine_Base::SetRacerData(URacerMatchManager* RacerManagerRef, bool IsReplacement)
{
	if (!RacerManagerRef) return;
	RacerManager = RacerManagerRef;
	RacerManager->AddParticipatedRace(RaceID, RaceLineID);
	SetRacerName(RacerManager->GetRacerName());
	OnRacerSetDelegate.Broadcast(RacerManager, RaceLineID);
}


void UGP_RaceLine_Base::SetRacerName(const FString& NewRacerName)
{
	NamesBox_RacerName->SetText(NewRacerName);
}

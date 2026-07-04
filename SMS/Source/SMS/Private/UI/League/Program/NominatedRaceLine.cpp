
#include "UI/League/Program/NominatedRaceLine.h"
#include "Managers/TeamManager.h"
#include "UI/BaseClasses/ChooseBox.h"
#include "UI/BaseClasses/NumbersBox.h"


void UNominatedRaceLine::SetRaceLineData(const FRaceLineData& NewRaceLineData)
{
	RaceLineData = NewRaceLineData;
	NumbersBox_RacerNumber->SetColour(RaceLineData.HelmetColour);
}


void UNominatedRaceLine::BindDelegates()
{
	Super::BindDelegates();
	ChooseBox_ChooseMainRacer->OnSelectionChangedDelegate.AddUObject(this, &UNominatedRaceLine::OnRacerChosen);
}


void UNominatedRaceLine::AddOption(const FRacerMatchData& Data, URacerManager* NewRacerManager)
{
	Super::AddOption(Data, NewRacerManager);
	ChooseBox_ChooseMainRacer->AddOption(Data.RacerData.Name);
	RacerManagers.Add(NewRacerManager, Data);
}

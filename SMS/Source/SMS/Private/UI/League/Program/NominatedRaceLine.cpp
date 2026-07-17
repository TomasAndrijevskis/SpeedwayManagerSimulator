
#include "UI/League/Program/NominatedRaceLine.h"
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


void UNominatedRaceLine::AddOption(FString SelectedItem)
{
	Super::AddOption(SelectedItem);
	ChooseBox_ChooseMainRacer->AddOption(SelectedItem);
}


void UNominatedRaceLine::RemoveFromReplacementSelection(FString SelectedItem)
{
	ChooseBox_RacerReplacement->RemoveOption(SelectedItem);
}


void UNominatedRaceLine::RemoveFromMainSelection(FString SelectedItem)
{
	ChooseBox_ChooseMainRacer->RemoveOption(SelectedItem);
	if (!ChooseBox_RacerReplacement->AnyOptionsLeft()) ChangeChooseBoxStatus(false);
}


void UNominatedRaceLine::LockChosenRacer()
{
	ChooseBox_ChooseMainRacer->SetIsEnabled(false);
}

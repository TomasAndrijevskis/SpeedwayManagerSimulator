
#include "UI/League/Program/NominatedRaceLine.h"
#include "Managers/RacerManager.h"
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


void UNominatedRaceLine::OnRacerChosen(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (RacerManager) OnSelectedRacerChangedDelegate.Broadcast(this, RacerManager);
	OnRacerChosenDelegate.Broadcast(this, SelectedItem);
}


void UNominatedRaceLine::OnRacerReplaced(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	ChooseBox_ChooseMainRacer->MakeChooseBoxUnavailable();
	Super::OnRacerReplaced(SelectedItem, SelectionType);
}


void UNominatedRaceLine::AddMainOption(FString SelectedItem)
{
	if (ChooseBox_ChooseMainRacer->DoesOptionExists(SelectedItem)) return;
	ChooseBox_ChooseMainRacer->AddOption(SelectedItem);
}


void UNominatedRaceLine::RemoveFromMainSelection(FString SelectedItem)
{
	ChooseBox_ChooseMainRacer->RemoveOption(SelectedItem);
	if (!ChooseBox_RacerReplacement->AnyOptionsLeft()) ChangeChooseBoxStatus(false);
}
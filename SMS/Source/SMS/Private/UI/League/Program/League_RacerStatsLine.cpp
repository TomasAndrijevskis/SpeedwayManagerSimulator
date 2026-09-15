
#include "SMS/Public/UI/League/Program/League_RacerStatsLine.h"
#include "Managers/RacerMatchManager.h"
#include "UI/BaseClasses/ChooseBox.h" 


void ULeague_RacerStatsLine::NativeConstruct()
{
	Super::NativeConstruct();
	ChooseBox_Racer->OnSelectionChangedDelegate.AddUObject(this, &ULeague_RacerStatsLine::OnRacerChosen);
}


void ULeague_RacerStatsLine::AddOption(const TObjectPtr<URacerMatchManager>& NewRacerManager)
{
	if (NewRacerManager)
	{
		Racers.Add(NewRacerManager);
		ChooseBox_Racer->AddOption(NewRacerManager->GetRacerName());
	}
	else ChooseBox_Racer->AddOption("");
}


void ULeague_RacerStatsLine::RemoveOption(const FString& Option)
{
	ChooseBox_Racer->RemoveOption(Option);
}


void ULeague_RacerStatsLine::OnRacerChosen(FString SelectedOption, ESelectInfo::Type SelectionType)
{
	if (PreviousOption == "")
	{
		PreviousOption = SelectedOption;
		TObjectPtr<URacerMatchManager> EmptyData = nullptr;
		OnSelectedOptionChangedDelegate.Broadcast(this, SelectedOption, EmptyData);
	}
	else
	{
		for (const auto& Racer : Racers)
		{
			if (Racer->GetRacerName() == PreviousOption)
			{
				SelectedData = Racer; break;
			}
		}
		OnSelectedOptionChangedDelegate.Broadcast(this, SelectedOption, SelectedData);
		PreviousOption = SelectedOption;
	}
	OnRacerSelectedDelegate.Broadcast(SelectedOption, RacerStatsLineID);
}


void ULeague_RacerStatsLine::ChooseRandomOption()
{
	if (ChooseBox_Racer->GetSelectedOption() != "") return;
	int OptionsAmount = ChooseBox_Racer->GetNumberOfOptions();
	int RandomOption = FMath::RandRange(0, OptionsAmount - 1);
	FString SelectedOption = ChooseBox_Racer->GetOptionAtIndex(RandomOption);
	if (SelectedOption == "")
	{
		if (ChooseBox_Racer->AnyOptionsLeft()) ChooseRandomOption();
	}
	else
	{
		ChooseBox_Racer->SetRandomOption(SelectedOption);
		OnRacerSelectedDelegate.Broadcast(SelectedOption, RacerStatsLineID);
	}
}


void ULeague_RacerStatsLine::LockRacer()
{
	ChooseBox_Racer->DisableChooseBox();
}


int32 ULeague_RacerStatsLine::GetNumberOfOptions() const{return ChooseBox_Racer->GetNumberOfOptions();}
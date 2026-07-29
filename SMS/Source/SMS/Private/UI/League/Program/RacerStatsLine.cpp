
#include "SMS/Public/UI/League/Program/RacerStatsLine.h"
#include "Components/HorizontalBox.h"
#include "Managers/RacerManager.h"
#include "UI/BaseClasses/ChooseBox.h" 
#include "UI/BaseClasses/NumbersBox.h"


void URacerStatsLine::NativeConstruct()
{
	Super::NativeConstruct();
	ChooseBox_Racer->OnSelectionChangedDelegate.AddUObject(this, &URacerStatsLine::OnRacerChosen);
}


void URacerStatsLine::InitializeManagers(URacerManager* RacerManagerRef)
{
	RacerManager = RacerManagerRef;
	BindDelegates();
}


void URacerStatsLine::BindDelegates()
{
	if (!RacerManager) return;
	RacerManager->OnPointsAddedDelegate.AddUObject(this, &URacerStatsLine::CreateNewPointsBox);
}


void URacerStatsLine::AddOption(const FRacerData Data)
{
	RacerData.Add(Data);
	ChooseBox_Racer->AddOption(Data.Name);
}


void URacerStatsLine::RemoveOption(const FString& Option)
{
	ChooseBox_Racer->RemoveOption(Option);
}


void URacerStatsLine::CreateNewPointsBox(const FString& Points, bool AddBonus)
{
	if (!PointsBoxClass || !RacerManager) return;
	UNumbersBox* NewNumbersBox = Cast<UNumbersBox>(CreateWidget(this, PointsBoxClass));
	if (!NewNumbersBox) return;
	if (AddBonus) NewNumbersBox->SetText(Points + "*");
	else NewNumbersBox->SetText(Points);
	HB_Points->AddChild(NewNumbersBox);
	UpdateOverallPoints(RacerManager->CountOverallPoints(), RacerManager->GetBonusAmount());
}


void URacerStatsLine::OnRacerChosen(FString SelectedOption, ESelectInfo::Type SelectionType)
{
	if (PreviousOption == "")
	{
		PreviousOption = SelectedOption;
		FRacerData EmptyData;
		OnSelectedOptionChangedDelegate.Broadcast(this, SelectedOption, EmptyData);
	}
	else
	{
		for (const auto& Data : RacerData)
		{
			if (Data.Name == PreviousOption)
			{
				SelectedData = Data; break;
			}
		}
		OnSelectedOptionChangedDelegate.Broadcast(this, SelectedOption, SelectedData);
		PreviousOption = SelectedOption;
	}
	OnRacerSelectedDelegate.Broadcast(SelectedOption, RacerStatsLineID);
}


void URacerStatsLine::ChooseRandomOption()
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


void URacerStatsLine::LockRacer()
{
	ChooseBox_Racer->DisableChooseBox();
}


void URacerStatsLine::UpdateOverallPoints(int32 Points, int32 Bonus)
{
	const FString NewText = FString::Printf(TEXT("%d+%d"), Points, Bonus);
	if (Bonus > 0) NumbersBox_OverallPoints->SetText(NewText);
	else NumbersBox_OverallPoints->SetText(Points);
}


void URacerStatsLine::SetID(int32 NewID)
{
	RacerStatsLineID = NewID;
	NumbersBox_RiderNumber->SetText(RacerStatsLineID);
}


int32 URacerStatsLine::GetID() const{return RacerStatsLineID;}
int32 URacerStatsLine::GetNumberOfOptions() const{return ChooseBox_Racer->GetNumberOfOptions();}
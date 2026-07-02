
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


void URacerStatsLine::AddOption(const FString& NewOption)
{
	ChooseBox_Racer->AddOption(NewOption);
}


void URacerStatsLine::CreateNewPointsBox(const FString& Points)
{
	if (!PointsBoxClass || !RacerManager) return;
	UNumbersBox* NewNumbersBox = Cast<UNumbersBox>(CreateWidget(this, PointsBoxClass));
	if (!NewNumbersBox) return;
	NewNumbersBox->SetText(Points);
	HB_Points->AddChild(NewNumbersBox);
	UpdateOverallPoints(RacerManager->CountOverallPoints());
}


void URacerStatsLine::OnRacerChosen(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	OnRacerChosenDelegate.Broadcast(SelectedItem, RacerStatsLineID);
}


void URacerStatsLine::ChooseRandomOption(TArray<int>& ChosenOptions)
{
	int OptionsAmount = ChooseBox_Racer->GetNumberOfOptions();
	int RandomOption = FMath::RandRange(0, OptionsAmount - 1);
	if (ChosenOptions.Contains(RandomOption))
	{
		ChooseRandomOption(ChosenOptions);
	}
	else
	{
		FString SelectedOption = ChooseBox_Racer->GetSelectedOption(RandomOption);
		ChooseBox_Racer->SetRandomOption(SelectedOption);
		OnRacerChosenDelegate.Broadcast(SelectedOption, RacerStatsLineID);
		ChosenOptions.Add(RandomOption);
	}
}


void URacerStatsLine::UpdateOverallPoints(int Points)
{
	NumbersBox_OverallPoints->SetText(Points);
}


void URacerStatsLine::SetID(int NewID)
{
	RacerStatsLineID = NewID;
	NumbersBox_RiderNumber->SetText(RacerStatsLineID);
}


int URacerStatsLine::GetID() const{return RacerStatsLineID;}
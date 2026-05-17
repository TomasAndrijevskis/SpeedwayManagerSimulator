
#include "UI/League/Programm/RacerStatsLine.h"
#include "Components/HorizontalBox.h"
#include "UI/BaseClasses/ChooseBox.h"
#include "UI/BaseClasses/NumbersBox.h"


void URacerStatsLine::NativeConstruct()
{
	Super::NativeConstruct();
	OnValueAddedDelegate.AddUObject(this, &URacerStatsLine::CreateNewPointsBox);
	NumbersBox_RiderNumber->SetText(FString::FromInt(ID));
	ChooseBox_Racer->OnSelectionChangedDelegate.AddUObject(this, &URacerStatsLine::OnRacerChosen);
}


void URacerStatsLine::AddPoints()
{
	if (!CanAddNewPointBox()) return;
	int RandomNumber = FMath::RandRange(0, 3);
	UE_LOG(LogTemp, Error, TEXT("New number: %i"), RandomNumber);
	RacerPoints.Add(FString::FromInt(RandomNumber));
	OnValueAddedDelegate.Broadcast(RacerPoints.Last());
}


void URacerStatsLine::CreateNewPointsBox(const FString& Points)
{
	if (!PointsBoxClass) return;
	UNumbersBox* NewNumbersBox = Cast<UNumbersBox>(CreateWidget(this, PointsBoxClass));
	if (!NewNumbersBox) return;
	NewNumbersBox->SetText(Points);
	HB_Points->AddChild(NewNumbersBox);
	UpdateOverallPoints(CountOverallPoints());
}


int URacerStatsLine::CountOverallPoints()
{
	if (!HB_Points->HasAnyChildren()) return 0;
	int sum = 0;
	for (const auto& Element : HB_Points->GetAllChildren())
	{
		int Number = Cast<UNumbersBox>(Element)->GetNumber();
		sum += Number;
	}
	return sum;
}


bool URacerStatsLine::CanAddNewPointBox() const
{
	if (HB_Points->GetChildrenCount() < MaxRacesAmount) return true;
	return false;
}


void URacerStatsLine::OnRacerChosen(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	OnRacerChosenDelegate.Broadcast(SelectedItem, ID);
}


void URacerStatsLine::UpdateOverallPoints(int Points)
{
	NumbersBox_OverallPoints->SetText(FString::FromInt(Points));
}

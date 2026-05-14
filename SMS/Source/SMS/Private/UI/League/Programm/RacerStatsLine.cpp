
#include "UI/League/Programm/RacerStatsLine.h"
#include "Components/HorizontalBox.h"
#include "UI/BaseClasses/NumbersBox.h"


void URacerStatsLine::NativeConstruct()
{
	Super::NativeConstruct();
	OnValueAddedDelegate.AddUObject(this, &URacerStatsLine::CreateNewPointsBox);
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
	NewNumbersBox->SetNumber(Points);
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


void URacerStatsLine::UpdateOverallPoints(int Points)
{
	NumbersBox_OverallPoints->SetNumber(FString::FromInt(Points));
}

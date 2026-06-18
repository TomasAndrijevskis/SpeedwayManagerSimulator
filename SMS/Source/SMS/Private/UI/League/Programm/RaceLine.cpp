
#include "SMS/Public/UI/League/Program/RaceLine.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/PanelWidget.h"
#include "Components/Slider.h"
#include "Data/RacersData/RacerData.h"
#include "Managers/RacerManager.h"
#include "UI/BaseClasses/ChooseBox.h"
#include "UI/BaseClasses/NamesBox.h"
#include "UI/BaseClasses/NumbersBox.h"


void URaceLine::NativeConstruct()
{
	Super::NativeConstruct();
	ChooseBox_RacerReplacement->OnSelectionChangedDelegate.AddUObject(this, &URaceLine::OnRacerReplaced);
}


void URaceLine::SetRacerData(const FRacerData& NewRacerData)
{
	RacerData = NewRacerData;
	SetRacerName(RacerData.Name);
}


void URaceLine::SetRacerName(const FString& NewRacerName)
{
	NamesBox_RacerName->SetText(NewRacerName);
}


void URaceLine::SetRaceLineData(const FColor& NewHelmetColour, int NewRacerID)
{
	RacerID = NewRacerID;
	NumbersBox_RacerNumber->SetText(RacerID);
	NumbersBox_RacerNumber->SetColour(NewHelmetColour);
}


void URaceLine::ChangeRider()
{
	USlider* NewSlider = CreateSlider();
	if (!NewSlider) return;
	UOverlaySlot* SliderSlot = Cast<UOverlaySlot>(Overlay_RacerName->AddChild(NewSlider));
	if (!SliderSlot) return;
	SliderSlot->SetHorizontalAlignment(HAlign_Fill);
	SliderSlot->SetVerticalAlignment(VAlign_Center);
}


void URaceLine::OnRacerReplaced(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	ChangeRider();
}


USlider* URaceLine::CreateSlider()
{
	if (!WidgetTree) return nullptr;
	USlider* NewSlider = WidgetTree->ConstructWidget<USlider>(USlider::StaticClass());
	if (!NewSlider) return nullptr;
	NewSlider->SetSliderBarColor(FColor::Black);
	NewSlider->SetSliderHandleColor(FColor::Transparent);
	return NewSlider;
}


void URaceLine::CalculateRating()
{
	int Start = FMath::RandRange(1,5);
	int Driving = FMath::RandRange(1,10);
	if (!GetIsVisitor()) Driving += FMath::RandRange(1,2);
	int RacerRating = RacerData.RacerStats.Rating;
	CurrentRacerRating = Start + Driving + RacerRating;
	UE_LOG(LogTemp, Warning, TEXT("Name: %s, Race rating: %i"), *RacerData.Name, CurrentRacerRating);
}


void URaceLine::SetPointsPerRace(int NewPoints)
{
	Points = NewPoints;
	NumbersBox_PointsPerRace->SetText(Points);
}


void URaceLine::OnRaceFinished()
{
	RacerData.RacerManager->OnValueAddRequestDelegate.Broadcast(FString::FromInt(Points));
}


int URaceLine::GetRaceLineID()const{return RaceLineID;}
int URaceLine::GetRacerID() const{return RacerID;}
int URaceLine::GetPointsPerRace() const{ return Points;}
int URaceLine::GetRacerRating() const{return CurrentRacerRating;}
bool URaceLine::GetIsVisitor() const {return RacerData.RacerManager->IsVisitor();}
void URaceLine::SetRaceLineID(int NewID){RaceLineID = NewID;}
void URaceLine::SetRacerID(int NewID){RacerID = NewID;}
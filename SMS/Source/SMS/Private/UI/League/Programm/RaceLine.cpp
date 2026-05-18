
#include "UI/League/Programm/RaceLine.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/PanelWidget.h"
#include "Components/Slider.h"
#include "UI/BaseClasses/ChooseBox.h"
#include "UI/BaseClasses/NamesBox.h"
#include "UI/BaseClasses/NumbersBox.h"


void URaceLine::NativeConstruct()
{
	Super::NativeConstruct();
	ChooseBox_RacerReplacement->OnSelectionChangedDelegate.AddUObject(this, &URaceLine::OnRacerReplaced);
	GenerateRandomNumber();
}


void URaceLine::SetRacerName(const FString& NewRacerName)
{
	NamesBox_RacerName->SetName(NewRacerName);
}


void URaceLine::SetRacerValues(const FColor& NewHelmetColour, int NewRacerNumber)
{
	ID = NewRacerNumber;
	NumbersBox_RacerNumber->SetText(FString::FromInt(NewRacerNumber));
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


void URaceLine::GenerateRandomNumber()
{
	RandomNumber = FMath::RandRange(0,100);
}


void URaceLine::SetPoints(int NewPoints)
{
	NumbersBox_PointsPerRace->SetText(FString::FromInt(NewPoints));
}


int URaceLine::GetGeneratedNumber()const{return RandomNumber;}
int URaceLine::GetID()const{return ID;}
void URaceLine::SetID(int NewID){ID = NewID;}
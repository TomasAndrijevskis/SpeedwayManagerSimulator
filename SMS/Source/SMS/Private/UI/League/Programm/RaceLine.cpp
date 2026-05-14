
#include "UI/League/Programm/RaceLine.h"
#include "Blueprint/WidgetTree.h"
#include "Components/ComboBoxString.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/PanelWidget.h"
#include "Components/Slider.h"
#include "UI/BaseClasses/NamesBox.h"
#include "UI/BaseClasses/NumbersBox.h"


void URaceLine::NativeConstruct()
{
	Super::NativeConstruct();
	SetRider(HelmetColour, RacerName, RacerNumber);
	ComboBox_RacerReplacement->OnSelectionChanged.AddUniqueDynamic(this, &URaceLine::OnSelectionChanged);
}


void URaceLine::SetRider(const FColor& NewHelmetColour, const FString& NewRacerName, const FString& NewRacerNumber)
{
	NumbersBox_RacerNumber->SetColour(NewHelmetColour);
	NumbersBox_RacerNumber->SetNumber(NewRacerNumber);
	NamesBox_RacerName->SetName(NewRacerName);
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


void URaceLine::OnSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
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


void URaceLine::SetPoints(int NewPoints)
{
	NumbersBox_PointsPerRace->SetNumber(FString::FromInt(NewPoints));
}
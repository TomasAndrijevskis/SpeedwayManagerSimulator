
#include "SMS/Public/UI/League/Program/RaceLine.h"
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


void URaceLine::SetRacerValues(const FColor& NewHelmetColour, int NewRacerID)
{
	RacerID = NewRacerID;
	if (RacerID <= 6) IsVisitor = false;
	else IsVisitor = true;
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


void URaceLine::GenerateRandomNumber()
{
	RandomNumber = FMath::RandRange(0,100);
}


void URaceLine::SetPoints(int NewPoints)
{
	Points = NewPoints;
	NumbersBox_PointsPerRace->SetText(Points);
}


int URaceLine::GetGeneratedNumber()const{return RandomNumber;}
int URaceLine::GetRaceLineID()const{return RaceLineID;}
int URaceLine::GetRacerID() const{return RacerID;}
int URaceLine::GetPoints() const{ return Points; }
bool URaceLine::GetIsVisitor() const {return IsVisitor;}
void URaceLine::SetIsVisitor(bool Visitor){IsVisitor = Visitor;}
void URaceLine::SetRaceLineID(int NewID){RaceLineID = NewID;}
void URaceLine::SetRacerID(int NewID){RacerID = NewID;}

#include "UI/League/Program/RaceLineBase.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/Slider.h"
#include "Managers/RacerManager.h"
#include "UI/BaseClasses/ChooseBox.h"
#include "UI/BaseClasses/NumbersBox.h"


void URaceLineBase::NativeConstruct()
{
	Super::NativeConstruct();
	ChooseBox_RacerReplacement->OnSelectionChangedDelegate.AddUObject(this, &URaceLineBase::OnRacerReplaced);
}


void URaceLineBase::SetRaceLineData(const FRaceLineData& NewRaceLineData)
{
	RacerID = NewRaceLineData.RacerID;
	RaceLineData = NewRaceLineData;
	if (RacerID != 0) NumbersBox_RacerNumber->SetText(RacerID);
	NumbersBox_RacerNumber->SetColour(NewRaceLineData.HelmetColour);
}


void URaceLineBase::SetRacerData(const FRacerMatchData& NewRacerData, URacerManager* RacerManagerRef)
{
	if (!RacerManagerRef || NewRacerData.RacerData.ID == INDEX_NONE) return;
	RacerData = NewRacerData;
	RacerManager = RacerManagerRef;
	SetRacerName(RacerData.RacerData.Name);
	BindDelegates();
}


void URaceLineBase::BindDelegates()
{
	if (!RacerManager) return;
	OnRaceStartedDelegate.AddUObject(this, &URaceLineBase::CalculateRating);
}


void URaceLineBase::CalculateRating()
{
	if (!RacerManager) return;
	RacerManager->SetTieBreaker();
	RacerManager->CalculateRating();
}


void URaceLineBase::SetPointsPerRace(int NewPoints)
{
	NumbersBox_PointsPerRace->SetText(NewPoints);
}


void URaceLineBase::OnRaceFinished()
{
	if (!RacerManager) return;
	RacerManager->OnValueAddRequestDelegate.Broadcast(NumbersBox_PointsPerRace->GetNumberAsString());
}


USlider* URaceLineBase::CreateSlider()
{
	if (!WidgetTree) return nullptr;
	USlider* NewSlider = WidgetTree->ConstructWidget<USlider>(USlider::StaticClass());
	if (!NewSlider) return nullptr;
	NewSlider->SetSliderBarColor(FColor::Black);
	NewSlider->SetSliderHandleColor(FColor::Transparent);
	return NewSlider;
}


void URaceLineBase::ChangeRider()
{
	USlider* NewSlider = CreateSlider();
	if (!NewSlider) return;
	UOverlaySlot* SliderSlot = Cast<UOverlaySlot>(Overlay_RacerName->AddChild(NewSlider));
	if (!SliderSlot) return;
	SliderSlot->SetHorizontalAlignment(HAlign_Fill);
	SliderSlot->SetVerticalAlignment(VAlign_Center);
}


void URaceLineBase::OnRacerReplaced(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	ChangeRider();
}


void URaceLineBase::SetRacerID(int NewRacerID){RacerID = NewRacerID;}
void URaceLineBase::SetRaceLineID(int NewID){RaceLineID = NewID;}
int URaceLineBase::GetRaceLineID()const{return RaceLineID;}
int URaceLineBase::GetRacerID()const{return RacerID;}
int URaceLineBase::GetTieBreaker()const{return RacerManager->GetTieBreaker();}
int URaceLineBase::GetRacerRating()const{return RacerManager->GetCurrentRaceRating();}
int URaceLineBase::GetPointsPerRace()const{return NumbersBox_PointsPerRace->GetNumber();}
bool URaceLineBase::IsVisitor()const{return RacerManager->IsVisitor();}
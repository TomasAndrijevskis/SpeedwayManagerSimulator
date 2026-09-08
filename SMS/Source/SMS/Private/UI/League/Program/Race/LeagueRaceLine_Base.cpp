
#include "Blueprint/WidgetTree.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/Slider.h"
#include "UI/League/Program/Race/League_RaceLine_Base.h"
#include "Managers/RacerMatchManager.h"
#include "UI/BaseClasses/ChooseBox.h"


void ULeague_RaceLine_Base::InitializeWidget()
{
	ChangeChooseBoxStatus(false);
	BindDelegates();
}


void ULeague_RaceLine_Base::SetRacerData(URacerMatchManager* RacerManagerRef, bool IsReplacement)
{
	if (!RacerManagerRef) return;
	RacerManager = RacerManagerRef;
	RacerManager->AddParticipatedRace(this);
	if(!IsReplacement)
	{
		OriginalRacerManager = RacerManager;
		SetRacerName(RacerManager->GetRacerName());
	}
	BindManagersDelegates();
	bIsRacerSet = true;
}


void ULeague_RaceLine_Base::BindDelegates()
{
	Super::BindDelegates();
	ChooseBox_RacerReplacement->OnSelectionChangedDelegate.AddUObject(this, &ULeague_RaceLine_Base::OnRacerReplaced);
}


void ULeague_RaceLine_Base::OnRacerReplaced(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (OriginalRacerManager != RacerManager) OnSelectedRacerChangedDelegate.Broadcast(this, RacerManager, true);
	OnRacerReplacedDelegate.Broadcast(this, SelectedItem, OriginalRacerManager);
	CrossOutRacer();
}


void ULeague_RaceLine_Base::AddReplacementOption(FString SelectedItem)
{
	if (ChooseBox_RacerReplacement->DoesOptionExists(SelectedItem)) return;
	ChooseBox_RacerReplacement->AddOption(SelectedItem);
}


void ULeague_RaceLine_Base::RemoveFromReplacementSelection(FString SelectedItem)
{
	ChooseBox_RacerReplacement->RemoveOption(SelectedItem);
	if (!ChooseBox_RacerReplacement->AnyOptionsLeft()) ChangeChooseBoxStatus(false);
}


void ULeague_RaceLine_Base::CrossOutRacer()
{
	USlider* NewSlider = CreateSlider();
	if (!NewSlider) return;
	UOverlaySlot* SliderSlot = Cast<UOverlaySlot>(Overlay_RacerName->AddChild(NewSlider));
	if (!SliderSlot) return;
	SliderSlot->SetHorizontalAlignment(HAlign_Fill);
	SliderSlot->SetVerticalAlignment(VAlign_Center);
}


USlider* ULeague_RaceLine_Base::CreateSlider()
{
	if (!WidgetTree) return nullptr;
	USlider* NewSlider = WidgetTree->ConstructWidget<USlider>(USlider::StaticClass());
	if (!NewSlider) return nullptr;
	NewSlider->SetSliderBarColor(FColor::Black);
	NewSlider->SetSliderHandleColor(FColor::Transparent);
	return NewSlider;
}


void ULeague_RaceLine_Base::ChangeChooseBoxStatus(bool Status)
{
	ChooseBox_RacerReplacement->SetIsEnabled(Status);
}


URacerMatchManager* ULeague_RaceLine_Base::GetOriginalRacerManager() const{return OriginalRacerManager;}
bool ULeague_RaceLine_Base::IsVisitor() const
{
	if (RacerManager) return RacerManager->IsVisitor();
	if (RaceLineData.HelmetColour == EHelmetColour::White || RaceLineData.HelmetColour == EHelmetColour::Yellow) return true;
	return false;
}

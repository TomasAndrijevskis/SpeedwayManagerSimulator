
#include "UI/League/Program/RaceLineBase.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/Slider.h"
#include "Gamemodes/SMS_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/MatchManager.h"
#include "Managers/RacerManager.h"
#include "Managers/TeamManager.h"
#include "UI/BaseClasses/ChooseBox.h"
#include "UI/BaseClasses/NumbersBox.h"


void URaceLineBase::NativeConstruct()
{
	Super::NativeConstruct();
	InitializeWidget();
}


void URaceLineBase::InitializeWidget()
{
	ASMS_GameMode* GameMode = Cast<ASMS_GameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	UMatchManager* MatchManager = GameMode->GetMatchManager();
	if (!MatchManager) return;
	MatchManager->OnRacerManagersCreatedDelegate.AddUObject(this, &URaceLineBase::SetTeamManager);
	BindDelegates();
	ChangeChooseBoxStatus(false);
}


void URaceLineBase::ChangeLineStatus(bool bIsActive)
{
	SetIsEnabled(bIsActive);
}


void URaceLineBase::ChangeChooseBoxStatus(bool Status)
{
	ChooseBox_RacerReplacement->SetIsEnabled(Status);
}


void URaceLineBase::SetRaceLineData(const FRaceLineData& NewRaceLineData)
{
	RaceLineData = NewRaceLineData;
	SetRacerNumber(RaceLineData.RacerID);
	NumbersBox_RacerNumber->SetColour(NewRaceLineData.HelmetColour);
}


void URaceLineBase::SetRacerData(URacerManager* RacerManagerRef, bool IsReplacement)
{
	if (!RacerManagerRef) return;
	RacerManager = RacerManagerRef;
	RacerManager->AddParticipatedRace(this);
	if(!IsReplacement) SetRacerName(RacerManager->GetRacerName());
	BindManagerDelegates();
	bIsRacerSet = true;
}


void URaceLineBase::BindManagerDelegates()
{
	if (!RacerManager) return;
	OnRaceStartedDelegate.AddUObject(RacerManager, &URacerManager::OnRaceStarted);
}


void URaceLineBase::BindDelegates()
{
	ChooseBox_RacerReplacement->OnSelectionChangedDelegate.AddUObject(this, &URaceLineBase::OnRacerReplaced);
}


void URaceLineBase::SetTeamManager(TArray<UTeamManager*> TeamManagersRef)
{
	for (const auto& Manager : TeamManagersRef)
	{
		if (!Manager) continue;
		if (RaceLineData.IsVisitorLine() == Manager->IsVisitorTeam())
		{
			TeamManager = Manager;
			break;
		}
	}
}


void URaceLineBase::SetPointsPerRace(const FString& NewPoints, bool AddBonus)
{
	NumbersBox_PointsPerRace->SetText(NewPoints);
	if (RacerManager) RacerManager->AddPoints(NewPoints, AddBonus);
}


void URaceLineBase::OnRacerChosen(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	OnRacerChosenDelegate.Broadcast(this, SelectedItem);
}


void URaceLineBase::OnRacerReplaced(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	OnRacerReplacedDelegate.Broadcast(this, SelectedItem);
	CrossOutRacer();
}


void URaceLineBase::AddReplacementOption(FString SelectedItem)
{
	ChooseBox_RacerReplacement->AddOption(SelectedItem);
}


void URaceLineBase::RemoveFromReplacementSelection(FString SelectedItem)
{
	ChooseBox_RacerReplacement->RemoveOption(SelectedItem);
	if (!ChooseBox_RacerReplacement->AnyOptionsLeft()) ChangeChooseBoxStatus(false);
}


void URaceLineBase::CrossOutRacer()
{
	USlider* NewSlider = CreateSlider();
	if (!NewSlider) return;
	UOverlaySlot* SliderSlot = Cast<UOverlaySlot>(Overlay_RacerName->AddChild(NewSlider));
	if (!SliderSlot) return;
	SliderSlot->SetHorizontalAlignment(HAlign_Fill);
	SliderSlot->SetVerticalAlignment(VAlign_Center);
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


void URaceLineBase::SetRacerNumber(int NewRacerNumber)
{
	RacerNumber = NewRacerNumber;
	if (RacerNumber != 0) NumbersBox_RacerNumber->SetText(RacerNumber);
}


void URaceLineBase::SetRaceLineID(int NewID){RaceLineID = NewID;}
int URaceLineBase::GetRacerNumber()const{return RacerNumber;}
int URaceLineBase::GetTieBreaker()const{return RacerManager->GetTieBreaker();}
int URaceLineBase::GetRacerRating()const{return RacerManager->GetCurrentRaceRating();}
int URaceLineBase::GetPointsPerRace()const{return NumbersBox_PointsPerRace->GetNumber();}
int URaceLineBase::GetTeamID()const{return TeamManager->GetTeamID();}
URacerManager* URaceLineBase::GetRacerManager()const{return RacerManager;}
UTeamManager* URaceLineBase::GetTeamManager()const{return TeamManager;}
FRaceLineData& URaceLineBase::GetRaceLineData(){return RaceLineData;}
bool URaceLineBase::IsRacerSet() const{return bIsRacerSet;}
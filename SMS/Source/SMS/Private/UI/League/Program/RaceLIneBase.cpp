
#include "UI/League/Program/RaceLineBase.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/Slider.h"
#include "Gamemodes/SMS_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/MatchManager.h"
#include "Managers/RaceFunctionLibrary.h"
#include "Managers/RacerManager.h"
#include "Managers/ScoreManager.h"
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
	ScoreManager = GameMode->GetScoreManager();
	UMatchManager* MatchManager = GameMode->GetMatchManager();
	if (!MatchManager || !ScoreManager) return;
	MatchManager->OnRacerManagersCreatedDelegate.AddUObject(this, &URaceLineBase::SetTeamManager);
	BindDelegates();
}


void URaceLineBase::HandleRace(bool bIsActive)
{
	SetIsEnabled(bIsActive);
	if (!ScoreManager) return;
	bool IsVisitor = RaceLineData.IsVisitor();
	bool CanReplace = URaceFunctionLibrary::IsReplacementPossible(
		ScoreManager->GetTeamScore(IsVisitor), ScoreManager->GetTeamScore(!IsVisitor));
	ChangeChooseBoxStatus(CanReplace);
	HandleFillingOptions(bIsActive, CanReplace);
}


void URaceLineBase::HandleFillingOptions(bool bIsActive, bool bCanReplace)
{
	if (bIsActive && bCanReplace) FillOptions();
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


void URaceLineBase::SetRacerData(const FRacerMatchData& NewRacerData, URacerManager* RacerManagerRef)
{
	if (!RacerManagerRef || NewRacerData.RacerData.ID == INDEX_NONE) return;
	RacerData = NewRacerData;
	RacerManager = RacerManagerRef;
	RacerManager->IncreaseRaceAmount();
	if(!IsReplacement) SetRacerName(RacerData.RacerData.Name);
	BindManagerDelegates();
}


void URaceLineBase::BindManagerDelegates()
{
	if (!RacerManager) return;
	OnRaceStartedDelegate.AddUObject(this, &URaceLineBase::OnRaceStarted);
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
		if (RaceLineData.IsVisitor() == Manager->IsVisitorTeam())
		{
			TeamManager = Manager;
			break;
		}
	}
}


void URaceLineBase::FillOptions()
{
	if (!TeamManager) return;
	TeamManager->ForEachRacerInLineup([this](const FRacerMatchData& Data, URacerManager* RacerManager)
	{
		if (!RacerManager) return;
		if (RacerManager->CanDriveMore()) AddOption(Data, RacerManager);
	});
}


void URaceLineBase::AddOption(const FRacerMatchData& Data, URacerManager* NewRacerManager)
{
	ChooseBox_RacerReplacement->AddOption(Data.RacerData.Name);
	RacerManagers.Add(NewRacerManager, Data);
}


void URaceLineBase::OnRaceStarted()
{
	if (!RacerManager) return;
	RacerManager->SetTieBreaker();
	RacerManager->CalculateRating(IsVisitor());
}


void URaceLineBase::SetPointsPerRace(const FString& NewPoints, bool AddBonus)
{
	NumbersBox_PointsPerRace->SetText(NewPoints);
	if (RacerManager) RacerManager->AddPoints(NewPoints, AddBonus);
}


void URaceLineBase::OnRacerChosen(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	FindSelectedRacer(SelectedItem, [this](URacerManager* Manager, const FRacerMatchData& Data)
	{
		SetRacerData(Data, Manager);
		SetRacerNumber(Data.RacerNumber);
	});
}


void URaceLineBase::OnRacerReplaced(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	FindSelectedRacer(SelectedItem, [this](URacerManager* Manager, const FRacerMatchData& Data)
	{
		IsReplacement = true;
		SetRacerData(Data, Manager);
		ChangeRider();
	});
}


void URaceLineBase::FindSelectedRacer(const FString& SelectedItem, const TFunction<void(URacerManager*, const FRacerMatchData&)>& Callback)
{
	for (const auto& Manager : RacerManagers)
	{
		if (Manager.Value.RacerData.Name == SelectedItem)
		{
			Callback(Manager.Key, Manager.Value);
			return;
		}
	}
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
int URaceLineBase::GetTeamID() const {return TeamManager->GetTeamID();}
bool URaceLineBase::IsVisitor()const{return RaceLineData.IsVisitor();}
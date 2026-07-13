
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
}


void URaceLineBase::ChangeLineStatus(bool bIsActive)
{
	SetIsEnabled(bIsActive);
}


void URaceLineBase::HandleRaceLine(bool IsTeamLosing)
{
	//if (!ScoreManager) return;
	/*bool CanReplace = URaceFunctionLibrary::IsReplacementPossible(
		ScoreManager->GetTeamScore(IsVisitor()), ScoreManager->GetTeamScore(!IsVisitor()));*/
	FillOptions(IsTeamLosing);
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


void URaceLineBase::SetRacerData(const FString& NewRacerName, URacerManager* RacerManagerRef)
{
	if (!RacerManagerRef) return;
	RacerManager = RacerManagerRef;
	RacerManager->AddParticipatedRace(this);
	if(!IsReplacement) SetRacerName(NewRacerName);
	BindManagerDelegates();
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


void URaceLineBase::FillOptions(bool IsTeamLosing)
{
	if (!TeamManager) return;
	TeamManager->GetAvailableReplacementRacers(IsTeamLosing, RacerManager, [this](const FRacerMatchData& Data, URacerManager* RacerManager)
	{
		AddOption(Data, RacerManager);
	});
	HandleAddedOptions();
}


void URaceLineBase::AddOption(const FRacerMatchData& Data, URacerManager* NewRacerManager)
{
	RacerManagers.Add(NewRacerManager, Data);
}


void URaceLineBase::HandleAddedOptions()
{
	if (RacerManagers.Num() > 0)
	{
		ChangeChooseBoxStatus(true);
		for (const auto& Manager : RacerManagers)
		{
			ChooseBox_RacerReplacement->AddOption(Manager.Value.RacerData.Name);
		}
	}
	else ChangeChooseBoxStatus(false);
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
		SetRacerData(Data.RacerData.Name, Manager);
		SetRacerNumber(Data.RacerNumber);
	});
}


void URaceLineBase::OnRacerReplaced(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	FindSelectedRacer(SelectedItem, [this](URacerManager* Manager, const FRacerMatchData& Data)
	{
		RacerManager->RemoveParticipatedRace(this);
		IsReplacement = true;
		SetRacerData(Data.RacerData.Name, Manager);
		OnRacerReplacedDelegate.Broadcast(this, Data.RacerData.Name);
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


void URaceLineBase::RemoveOption(FString SelectedItem)
{
	ChooseBox_RacerReplacement->RemoveOption(SelectedItem);
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
bool URaceLineBase::IsVisitor()const{return RaceLineData.IsVisitorLine();}
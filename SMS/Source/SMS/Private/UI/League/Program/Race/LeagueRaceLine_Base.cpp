
#include "Blueprint/WidgetTree.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/Slider.h"
#include "UI/League/Program/Race/League_RaceLine_Base.h"
#include "Gamemodes/SMS_GameMode.h"
#include "Managers/RacerManager.h"
#include "Managers/TeamManager.h"
#include "Rules/LeagueRules.h"
#include "Subsystems/MatchManagerSubsystem.h"
#include "UI/BaseClasses/ChooseBox.h"


void ULeague_RaceLine_Base::InitializeWidget()
{
	if (UMatchManagerSubsystem* MatchManagerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMatchManagerSubsystem>())
	{
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		Cast<ULeagueRules>(MatchManagerSubsystem->GetCompetitionRules())->OnRacerManagersCreatedDelegate.AddUObject(this, &ULeague_RaceLine_Base::SetTeamManager);
	}
	ChangeChooseBoxStatus(false);
	BindDelegates();
}


void ULeague_RaceLine_Base::SetRacerData(URacerManager* RacerManagerRef, bool IsReplacement)
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


void ULeague_RaceLine_Base::SetTeamManager(TArray<UTeamManager*> TeamManagersRef)
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


ETeams ULeague_RaceLine_Base::GetTeam()const{return TeamManager->GetTeam();}
URacerManager* ULeague_RaceLine_Base::GetOriginalRacerManager() const{return OriginalRacerManager;}
UTeamManager* ULeague_RaceLine_Base::GetTeamManager()const{return TeamManager;}

#include "UI/League/Program/NominatedRaceLine.h"
#include "Gamemodes/SMS_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/MatchManager.h"
#include "Managers/TeamManager.h"
#include "UI/BaseClasses/ChooseBox.h"
#include "UI/BaseClasses/NumbersBox.h"


void UNominatedRaceLine::NativeConstruct()
{
	Super::NativeConstruct();
	InitializeWidget();
	ChooseBox_ChooseRacer->OnSelectionChangedDelegate.AddUObject(this, &UNominatedRaceLine::OnRacerChosen);
}


void UNominatedRaceLine::SetRaceLineData(const FRaceLineData& NewRaceLineData)
{
	RaceLineData = NewRaceLineData;
	NumbersBox_RacerNumber->SetColour(RaceLineData.HelmetColour);
}


void UNominatedRaceLine::InitializeWidget()
{
	ASMS_GameMode* GameMode = Cast<ASMS_GameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	UMatchManager* MatchManager = GameMode->MatchManager;
	if (!MatchManager) return;
	MatchManager->OnRacerManagersCreatedDelegate.AddUObject(this, &UNominatedRaceLine::SetTeamManager);
}


void UNominatedRaceLine::SetTeamManager(TArray<UTeamManager*> TeamManagersRef)
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
	FillOptions();
}


void UNominatedRaceLine::OnRacerChosen(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	for (const auto Manager : RacerManagers)
	{
		if (Manager.Value.RacerData.Name == SelectedItem)
		{
			SetRacerData(Manager.Value, Manager.Key);
			return;
		}
	}
}


void UNominatedRaceLine::FillOptions()
{
	if (!TeamManager) return;
	TeamManager->ForEachRacerInLineup([this](const FRacerMatchData& Data, URacerManager* Manager)
	{
		AddOption(Data, Manager);
	});
}


void UNominatedRaceLine::AddOption(const FRacerMatchData& Data, URacerManager* NewRacerManager)
{
	//FString Option = Data.RacerData.Name + " - " + FString::FromInt(NewRacerManager->CountOverallPoints()); 
	//ChooseBox_ChooseRacer->AddOption(Option);
	ChooseBox_ChooseRacer->AddOption(Data.RacerData.Name);
	RacerManagers.Add(NewRacerManager, Data);
}

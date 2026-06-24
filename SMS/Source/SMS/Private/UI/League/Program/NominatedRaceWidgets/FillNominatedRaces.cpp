
#include "UI/League/Program/NominatedRaceWidgets/FillNominatedRaces.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Gamemodes/SMS_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/MatchManager.h"
#include "UI/League/Program/NominatedRaceWidgets/NominatedRace.h"


void UFillNominatedRaces::InitializeManagers()
{
	ASMS_GameMode* GameMode = Cast<ASMS_GameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	MatchManager = GameMode->MatchManager;
}


void UFillNominatedRaces::InitializeWidget()
{
	BindDelegates();
	CreateNominatedRaces();
}


void UFillNominatedRaces::CreateNominatedRaces()
{
	if (!MatchManager) return;
	const int CurrentRace = MatchManager->GetCurrentRaceNumber();
	const int AmountOfRaces = MatchManager->GetAmountOfRaces();
	int Number = AmountOfRaces - CurrentRace;
	for (int i = CurrentRace; i < Number; i++)
	{
		UNominatedRace* NewNominatedRace = CreateNominatedRace();
		if (!NewNominatedRace) return;
		VB_Content->AddChildToVerticalBox(NewNominatedRace);
		NewNominatedRace->InitializeWidget(i);
		NominatedRaces.Add(NewNominatedRace);
	}
}


UNominatedRace* UFillNominatedRaces::CreateNominatedRace()
{
	if (!NominatedRaceClass) return nullptr;
	UNominatedRace* NewNominatedRace = CreateWidget<UNominatedRace>(this, NominatedRaceClass);
	if (!NewNominatedRace) return nullptr;
	return NewNominatedRace;
}


void UFillNominatedRaces::BindDelegates()
{
	Button_Confirm->OnClicked.AddUniqueDynamic(this, &UFillNominatedRaces::RemoveWidget);
}


void UFillNominatedRaces::RemoveWidget()
{
	OnConfirmedDelegate.Broadcast(false);
	this->RemoveFromParent();
	OnConfirmedDelegate.Clear();
}

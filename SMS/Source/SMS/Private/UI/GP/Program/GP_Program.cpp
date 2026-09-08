
#include "UI/GP/Program/GP_Program.h"
#include "Components/Button.h"


//for testing
#include "Gamemodes/SMS_GameMode.h"
#include "Kismet/GameplayStatics.h"


void UGPProgram::NativeConstruct()
{
	Super::NativeConstruct();
	BindDelegates();
	CreateRaces();
	CreateRaceStatsWidget();
}

/*
void UGPProgram::InitializeManagers()
{
	GameMode = Cast<ASMS_GameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	GameMode->CreateManagers();
	MatchManager = GameMode->GetMatchManager();
}*/


void UGPProgram::BindDelegates()
{
	Super::BindDelegates();
	Button_RandomizeLineup->OnClicked.AddUniqueDynamic(this, &UGPProgram::HandleLineup);
}


void UGPProgram::HandleLineup()
{
	/*if (!GameMode) return;
	TArray<TObjectPtr<URacerCareerManager>> Racers = GameMode->GetTopRacers();
	if (Racers.IsEmpty()) return;*/
	
}


void UGPProgram::DisableButtons()
{
	Button_RandomizeLineup->SetIsEnabled(false);
}


void UGPProgram::PopulateRacers()
{
	
}

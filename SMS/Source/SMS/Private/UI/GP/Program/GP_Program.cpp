
#include "UI/GP/Program/GP_Program.h"
#include "Components/Button.h"


#include "Gamemodes/SMS_GameMode.h"
#include "Kismet/GameplayStatics.h"


void UGPProgram::InitializeManagers()
{
	ASMS_GameMode* GameMode = Cast<ASMS_GameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	GameMode->CreateManagers();
	MatchManager = GameMode->GetMatchManager();
}

void UGPProgram::NativeConstruct()
{
	Super::NativeConstruct();
	BindDelegates();
	CreateRaces();
	CreateRaceStatsWidget();
}


void UGPProgram::DisableButtons()
{
	Super::DisableButtons();
	Button_RandomizeLineup->SetIsEnabled(false);
}

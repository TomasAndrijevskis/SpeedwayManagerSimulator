
#include "UI/Calendar/Calendar.h"
#include "Components/Button.h"
#include "Gamemodes/SMS_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "SMS/Public/UI/League/Program/LeagueProgram.h"
#include "UI/BaseClasses/NamesBox.h"


void UCalendar::NativeConstruct()
{
	Super::NativeConstruct();
	GameMode = Cast<ASMS_GameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	MatchManager = GameMode->MatchManager;
	if (!MatchManager) return;
	Button_StartMatch->OnClicked.AddUniqueDynamic(this, &UCalendar::StartMatch);
	GetRandomTeams();
}


void UCalendar::GetRandomTeams()
{
	if (!GameMode) return;
	int NumberOfTeams = GameMode->GetTeamsAmount();
	if (NumberOfTeams <= 0) return;
	int HomeTeamID = FMath::RandRange(1, NumberOfTeams);
	int VisitorTeamID = FMath::RandRange(1, NumberOfTeams);
	UE_LOG(LogTemp, Warning, TEXT("Home team id: %i"), HomeTeamID);
	UE_LOG(LogTemp, Warning, TEXT("Visitor team id: %i"), VisitorTeamID);
	HomeTeamData = GameMode->GetTeamData(HomeTeamID);
	VisitorTeamData = GameMode->GetTeamData(VisitorTeamID);
	CreateMatch();
}


void UCalendar::CreateMatch()
{
	FText HTeamName  = StaticEnum<ETeams>()->GetDisplayNameTextByValue(HomeTeamData->TeamID);
	FText VTeamName = StaticEnum<ETeams>()->GetDisplayNameTextByValue(VisitorTeamData->TeamID);
	UE_LOG(LogTemp, Warning, TEXT("Home team: %s"), *HTeamName.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Visitor team: %s"), *VTeamName.ToString());
	NamesBox_HomeText->SetName("Home Team");
	NamesBox_VisitorText->SetName("Visitor Team");
	NamesBox_HomeTeamName->SetName(HTeamName.ToString());
	NamesBox_VisitorTeamName->SetName(VTeamName.ToString());
}


void UCalendar::StartMatch()
{
	if (!LeagueProgramClass) return;
	ULeagueProgram* LeagueProgram = CreateWidget<ULeagueProgram>(this, LeagueProgramClass);
	if (!LeagueProgram) return;
	LeagueProgram->AddToViewport(1);
	FText HTeamName  = StaticEnum<ETeams>()->GetDisplayNameTextByValue(HomeTeamData->TeamID);
	FText VTeamName = StaticEnum<ETeams>()->GetDisplayNameTextByValue(VisitorTeamData->TeamID);
	LeagueProgram->CreateTeam(false, HTeamName.ToString(), *HomeTeamData);
	LeagueProgram->CreateTeam(true, VTeamName.ToString(), *VisitorTeamData);
}


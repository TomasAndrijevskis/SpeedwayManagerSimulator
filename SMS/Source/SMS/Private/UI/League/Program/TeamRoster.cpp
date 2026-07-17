
#include "SMS/Public/UI/League/Program/TeamRoster.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Gamemodes/SMS_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/ScoreManager.h"
#include "Managers/TeamManager.h"
#include "UI/BaseClasses/NamesBox.h"
#include "UI/BaseClasses/NumbersBox.h"
#include "SMS/Public/UI/League/Program/RacerStatsLine.h"


void UTeamRoster::InitializeTeam(FTeamMatchData* NewTeamData)
{
	if (!NewTeamData) return;
	TeamID = NewTeamData->TeamID;
	InitializeManagers(NewTeamData);
	BindDelegates();
	CreateRacerStatLines();
	DisplayTeamName();
	DisplayTeamStatus();
}


void UTeamRoster::InitializeManagers(FTeamMatchData* NewTeamData)
{
	if (!NewTeamData) return;
	ASMS_GameMode* GameMode = Cast<ASMS_GameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	ScoreManager = GameMode->GetScoreManager();
	TeamManager = NewObject<UTeamManager>(this);
	if (!TeamManager || !ScoreManager) return;
	TeamManager->SetTeamData(NewTeamData);
	ScoreManager->AddTeamRef(NewTeamData);
}


void UTeamRoster::BindDelegates()
{
	if (!ScoreManager) return;
	ScoreManager->OnTeamOverallScoreUpdatedDelegate.AddUObject(this, &UTeamRoster::UpdateTeamPoints);
}


void UTeamRoster::CreateRacerStatLines()
{
	if (!TeamManager) return;
	int Id = 1;
	if (TeamManager->IsVisitorTeam()) Id = 7;
	for (int i = 0; i < RacersAmount; i++, Id++)
	{
		URacerStatsLine* NewStatLine = CreateRacerStatLine(Id);
		if (NewStatLine)
		{
			UVerticalBoxSlot* VB_Slot = VB_Content->AddChildToVerticalBox(NewStatLine);
			if (VB_Slot)
			{
				VB_Slot->SetHorizontalAlignment(HAlign_Fill);
				VB_Slot->SetVerticalAlignment(VAlign_Fill);
			}
			TeamManager->AddRacerStatsLine(NewStatLine);
			NewStatLine->OnRacerSelectedDelegate.AddUObject(TeamManager, &UTeamManager::AddRacersToLineup);
		}
	}
	TeamManager->FillTeamRosterOptions();
}


URacerStatsLine* UTeamRoster::CreateRacerStatLine(int ID)
{
	if (!RacerStatsLineClass) return nullptr;
	URacerStatsLine* NewStatLine = CreateWidget<URacerStatsLine>(this, RacerStatsLineClass);
	if (!NewStatLine) return nullptr;
	NewStatLine->SetID(ID);
	return NewStatLine;
}


void UTeamRoster::DisplayTeamName()
{
	if (!TeamManager) return;
	NamesBox_TeamName->SetText(TeamManager->GetTeamName());
}


void UTeamRoster::UpdateTeamPoints(int TeamId, int NewPoints)
{
	if (TeamID == TeamId) NumbersBox_TeamPoints->SetText(NewPoints);
}


void UTeamRoster::DisplayTeamStatus()
{
	if (!TeamManager) return;
	if (TeamManager->IsVisitorTeam()) NamesBox_TeamStatus->SetText("Visitor");
	else NamesBox_TeamStatus->SetText("Home");
}


UTeamManager* UTeamRoster::GetTeamManager() const{return TeamManager;}

#include "SMS/Public/UI/League/Program/TeamRoster.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Managers/ScoreManager.h"
#include "Managers/TeamManager.h"
#include "Rules/LeagueRules.h"
#include "UI/BaseClasses/NamesBox.h"
#include "UI/BaseClasses/NumbersBox.h"
#include "SMS/Public/UI/League/Program/League_RacerStatsLine.h"
#include "Subsystems/MatchManagerSubsystem.h"


void UTeamRoster::InitializeTeam(FTeamMatchData* NewTeamData)
{
	if (!NewTeamData) return;
	Team = NewTeamData->Team;
	InitializeManagers(NewTeamData);
	BindDelegates();
	CreateRacerStatLines(ScoreManager);
	DisplayTeamName();
	DisplayTeamStatus();
}


void UTeamRoster::InitializeManagers(FTeamMatchData* NewTeamData)
{
	if (!NewTeamData) return;
	if (UMatchManagerSubsystem* MatchManagerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMatchManagerSubsystem>())
	{
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		ScoreManager = Cast<ULeagueRules>(MatchManagerSubsystem->GetCompetitionRules())->GetScoreManager();
	}
	
	TeamManager = NewObject<UTeamManager>(this);
	if (!TeamManager || !ScoreManager) return;
	TeamManager->InitializeManager();
	TeamManager->SetTeamData(NewTeamData);
	ScoreManager->AddTeamRef(NewTeamData);
}


void UTeamRoster::BindDelegates()
{
	if (!ScoreManager) return;
	ScoreManager->OnTeamOverallScoreUpdatedDelegate.AddUObject(this, &UTeamRoster::UpdateTeamPoints);
}


void UTeamRoster::CreateRacerStatLines(const UScoreManager* ScoreManagerRef)
{
	if (!TeamManager) return;
	int32 Id = 1;
	if (TeamManager->IsVisitorTeam()) Id = 7;
	for (int32 i = 0; i < RacersAmount; i++, Id++)
	{
		ULeague_RacerStatsLine* NewStatLine = CreateRacerStatLine(Id);
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
			NewStatLine->OnSelectedOptionChangedDelegate.AddUObject(TeamManager, &UTeamManager::UpdateStatsLineOptions);
		}
	}
	TeamManager->SetScoreManager(ScoreManager);
	TeamManager->FillTeamRosterOptions();
}


ULeague_RacerStatsLine* UTeamRoster::CreateRacerStatLine(int32 ID)
{
	if (!RacerStatsLineClass) return nullptr;
	ULeague_RacerStatsLine* NewStatLine = CreateWidget<ULeague_RacerStatsLine>(this, RacerStatsLineClass);
	if (!NewStatLine) return nullptr;
	NewStatLine->SetID(ID);
	return NewStatLine;
}


void UTeamRoster::DisplayTeamName()
{
	if (!TeamManager) return;
	NamesBox_TeamName->SetText(TeamManager->GetTeamName());
}


void UTeamRoster::UpdateTeamPoints(ETeams TeamToUpdate, int32 NewPoints)
{
	if (Team == TeamToUpdate) NumbersBox_TeamPoints->SetText(NewPoints);
}


void UTeamRoster::DisplayTeamStatus()
{
	if (!TeamManager) return;
	if (TeamManager->IsVisitorTeam()) NamesBox_TeamStatus->SetText("Visitor");
	else NamesBox_TeamStatus->SetText("Home");
}


UTeamManager* UTeamRoster::GetTeamManager() const{return TeamManager;}
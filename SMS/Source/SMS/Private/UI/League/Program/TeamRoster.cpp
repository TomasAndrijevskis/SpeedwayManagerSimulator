
#include "SMS/Public/UI/League/Program/TeamRoster.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Managers/MatchManager.h"
#include "Managers/ScoreManager.h"
#include "Managers/TeamManager.h"
#include "UI/BaseClasses/NamesBox.h"
#include "UI/BaseClasses/NumbersBox.h"
#include "SMS/Public/UI/League/Program/RacerStatsLine.h"


void UTeamRoster::InitializeTeam(FTeamMatchData* NewTeamData, const UMatchManager* MatchManagerRef)
{
	if (!NewTeamData) return;
	TeamID = NewTeamData->TeamID;
	InitializeManagers(NewTeamData, MatchManagerRef);
	BindDelegates();
	CreateRacerStatLines(ScoreManager);
	DisplayTeamName();
	DisplayTeamStatus();
}


void UTeamRoster::InitializeManagers(FTeamMatchData* NewTeamData, const UMatchManager* MatchManagerRef)
{
	if (!NewTeamData) return;
	ScoreManager = MatchManagerRef->GetScoreManager();
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
			NewStatLine->OnSelectedOptionChangedDelegate.AddUObject(TeamManager, &UTeamManager::UpdateStatsLineOptions);
		}
	}
	TeamManager->SetScoreManager(ScoreManager);
	TeamManager->FillTeamRosterOptions();
}


URacerStatsLine* UTeamRoster::CreateRacerStatLine(int32 ID)
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


void UTeamRoster::UpdateTeamPoints(int32 TeamId, int32 NewPoints)
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
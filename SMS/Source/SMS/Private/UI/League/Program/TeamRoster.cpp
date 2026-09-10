
#include "SMS/Public/UI/League/Program/TeamRoster.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Managers/TeamManager.h"
#include "Rules/League_Rules.h"
#include "UI/BaseClasses/NamesBox.h"
#include "UI/BaseClasses/NumbersBox.h"
#include "SMS/Public/UI/League/Program/League_RacerStatsLine.h"
#include "Subsystems/MatchManagerSubsystem.h"


void UTeamRoster::InitializeTeam(bool IsVisitor)
{
	InitializeManagers(IsVisitor);
	BindDelegates();
	CreateRacerStatLines();
	DisplayTeamName();
	DisplayTeamStatus();
}


void UTeamRoster::InitializeManagers(bool IsVisitor)
{
	if (UMatchManagerSubsystem* MatchManagerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMatchManagerSubsystem>())
	{
		TeamManager = Cast<ULeague_Rules>(MatchManagerSubsystem->GetCompetitionRules())->GetTeamManager(IsVisitor);
	}
}


void UTeamRoster::BindDelegates()
{
	if (!TeamManager) return;
	TeamManager->OnTeamScoreUpdatedDelegate.AddUObject(this, &UTeamRoster::UpdateTeamPoints);
}


void UTeamRoster::CreateRacerStatLines()
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


void UTeamRoster::UpdateTeamPoints(int32 NewPoints)
{
	NumbersBox_TeamPoints->SetText(NewPoints);
}


void UTeamRoster::DisplayTeamStatus()
{
	if (!TeamManager) return;
	if (TeamManager->IsVisitorTeam()) NamesBox_TeamStatus->SetText("Visitor");
	else NamesBox_TeamStatus->SetText("Home");
}


UTeamManager* UTeamRoster::GetTeamManager() const{return TeamManager;}
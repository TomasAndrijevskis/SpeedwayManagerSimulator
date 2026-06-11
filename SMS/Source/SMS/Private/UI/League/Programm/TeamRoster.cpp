
#include "SMS/Public/UI/League/Program/TeamRoster.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "UI/BaseClasses/NamesBox.h"
#include "UI/BaseClasses/NumbersBox.h"
#include "SMS/Public/UI/League/Program/RacerStatsLine.h"


void UTeamRoster::NativeConstruct()
{
	Super::NativeConstruct();
	InitializeManagers();
	CreateRacerStatLines();
	SetTeamName();
	FillTeamRosters();
}


void UTeamRoster::InitializeManagers()
{
	TeamRosterManager = NewObject<UTeamRostersManager>(this);
	if (!TeamRosterManager) return;
	TeamRosterManager->SetTeamData(TeamData);
}


void UTeamRoster::CreateRacerStatLines()
{
	if (!TeamRosterManager) return;
	int Id = 1;
	if (IsVisitorTeam) Id = 7;
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
			RacersLines.Add(NewStatLine);
			NewStatLine->OnPointsUpdatedDelegate.AddUObject(this, &UTeamRoster::UpdateTeamPoints);
			NewStatLine->OnRacerChosenDelegate.AddUObject(TeamRosterManager, &UTeamRostersManager::AddRacer);
		}
	}
}


URacerStatsLine* UTeamRoster::CreateRacerStatLine(int ID)
{
	if (!RacerStatsLineClass) return nullptr;
	URacerStatsLine* NewStatLine = CreateWidget<URacerStatsLine>(this, RacerStatsLineClass);
	if (!NewStatLine) return nullptr;
	NewStatLine->SetID(ID);
	return NewStatLine;
}


void UTeamRoster::FillTeamRosters()
{
	for (const auto& RacerLine : RacersLines)
	{
		for (const auto& RacerData : TeamData.Racers)
		{
			RacerLine->AddOption(RacerData.Key);
		}
	}
}


void UTeamRoster::SetTeamName()
{
	NamesBox_TeamName->SetText(TeamData.TeamName);
}


void UTeamRoster::UpdateTeamPoints(int NewPoints)
{
	NumbersBox_TeamPoints->AddNumber(NewPoints);
}


void UTeamRoster::SetTeamStatus(bool isVisitorTeam)
{
	IsVisitorTeam = isVisitorTeam;
	if (IsVisitorTeam) NamesBox_TeamStatus->SetText("Visitor");
	else NamesBox_TeamStatus->SetText("Home");
}


void UTeamRoster::SetTeamData(const FTeamRosterData& NewTeamData){TeamData = NewTeamData;}
TArray<URacerStatsLine*>& UTeamRoster::GetRacers(){return RacersLines;}
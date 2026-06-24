
#include "SMS/Public/UI/League/Program/TeamRoster.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Gamemodes/SMS_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/ScoreManager.h"
#include "UI/BaseClasses/NamesBox.h"
#include "UI/BaseClasses/NumbersBox.h"
#include "SMS/Public/UI/League/Program/RacerStatsLine.h"


void UTeamRoster::NativeConstruct()
{
	Super::NativeConstruct();
	InitializeManagers();
	BindDelegates();
	CreateRacerStatLines();
	SetTeamName();
	FillTeamRosterOptions();
}


void UTeamRoster::InitializeTeam(int NewTeamID, bool bStatus)
{
	TeamID = NewTeamID;
	IsVisitorTeam = bStatus;
	SetTeamStatus();
}


void UTeamRoster::InitializeManagers()
{
	ASMS_GameMode* GameMode = Cast<ASMS_GameMode>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	ScoreManager = GameMode->ScoreManager;
	TeamManager = NewObject<UTeamManager>(this);
	if (!TeamManager || !ScoreManager) return;
	TeamManager->SetTeamData(TeamID);
}


void UTeamRoster::BindDelegates()
{
	if (!ScoreManager) return;
	if (IsVisitorTeam) ScoreManager->OnVisitorPtsUpdatedDelegate.AddUObject(this, &UTeamRoster::UpdateTeamPoints);
	else ScoreManager->OnHomePtsUpdatedDelegate.AddUObject(this, &UTeamRoster::UpdateTeamPoints);
}


void UTeamRoster::CreateRacerStatLines()
{
	if (!TeamManager) return;
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
			RacerStatsLines.Add(NewStatLine);
			NewStatLine->OnRacerChosenDelegate.AddUObject(TeamManager, &UTeamManager::AddRacersToLineup);
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


void UTeamRoster::FillTeamRosterOptions()
{
	for (const auto& RacerLine : RacerStatsLines)
	{
		TeamManager->ForEachRacerInRoster([this, RacerLine](const FRacerData& Data)
		{
			RacerLine->AddOption(Data.Name);
		});
	}
}


void UTeamRoster::SetTeamName()
{
	NamesBox_TeamName->SetText(TeamManager->GetTeamName());
}


void UTeamRoster::UpdateTeamPoints(int NewPoints)
{
	NumbersBox_TeamPoints->SetText(NewPoints);
}


void UTeamRoster::SetTeamStatus()
{
	if (IsVisitorTeam) NamesBox_TeamStatus->SetText("Visitor");
	else NamesBox_TeamStatus->SetText("Home");
}


TArray<URacerStatsLine*>& UTeamRoster::GetRacerStatsLines(){return RacerStatsLines;}

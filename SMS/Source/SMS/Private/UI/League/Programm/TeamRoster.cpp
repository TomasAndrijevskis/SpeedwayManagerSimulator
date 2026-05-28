
#include "SMS/Public/UI/League/Program/TeamRoster.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "UI/BaseClasses/NamesBox.h"
#include "UI/BaseClasses/NumbersBox.h"
#include "SMS/Public/UI/League/Program/RacerStatsLine.h"


void UTeamRoster::NativeConstruct()
{
	Super::NativeConstruct();
	CreateRacerStatLines();
	FillTeamLineups();
	NamesBox_TeamName->SetText(TeamName);
}


void UTeamRoster::CreateRacerStatLines()
{
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
			Racers.Add(NewStatLine);
			NewStatLine->OnPointsUpdatedDelegate.AddUObject(this, &UTeamRoster::UpdateTeamPoints);
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


void UTeamRoster::FillTeamLineups()
{
}


void UTeamRoster::FillTeamData(URacerStatsLine* const& Racer,  TArray<FRacerStats> TeamData)
{

}


void UTeamRoster::UpdateTeamPoints(int NewPoints)
{
	NumbersBox_TeamPoints->AddNumber(NewPoints);
}


void UTeamRoster::SetIsVisitorTeam(bool isVisitorTeam)
{
	IsVisitorTeam = isVisitorTeam;
	if (isVisitorTeam) NamesBox_TeamStatus->SetText("Visitor");
	else NamesBox_TeamStatus->SetText("Home");
}


void UTeamRoster::SetTeamName(const FString& NewTeamName){TeamName = NewTeamName;}
TArray<URacerStatsLine*>& UTeamRoster::GetRacers(){return Racers;}

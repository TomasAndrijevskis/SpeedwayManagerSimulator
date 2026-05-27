
#include "SMS/Public/UI/League/Program/TeamLineup.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "UI/BaseClasses/NamesBox.h"
#include "UI/BaseClasses/NumbersBox.h"
#include "SMS/Public/UI/League/Program/RacerStatsLine.h"


void UTeamLineup::NativeConstruct()
{
	Super::NativeConstruct();
	CreateRacerStatLines();
	FillTeamLineups();
	NamesBox_TeamName->SetName(TeamName);
}


void UTeamLineup::CreateRacerStatLines()
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
			NewStatLine->OnPointsUpdatedDelegate.AddUObject(this, &UTeamLineup::UpdateTeamPoints);
		}
	}
}


URacerStatsLine* UTeamLineup::CreateRacerStatLine(int ID)
{
	if (!RacerStatsLineClass) return nullptr;
	URacerStatsLine* NewStatLine = CreateWidget<URacerStatsLine>(this, RacerStatsLineClass);
	if (!NewStatLine) return nullptr;
	NewStatLine->SetID(ID);
	return NewStatLine;
}


void UTeamLineup::FillTeamLineups()
{
}


void UTeamLineup::FillTeamData(URacerStatsLine* const& Racer,  TArray<FRacerStats> TeamData)
{

}


void UTeamLineup::UpdateTeamPoints(int NewPoints)
{
	NumbersBox_TeamPoints->AddNumber(NewPoints);
}


void UTeamLineup::SetIsVisitorTeam(bool isVisitorTeam)
{
	IsVisitorTeam = isVisitorTeam;
	if (isVisitorTeam) NamesBox_TeamStatus->SetName("Visitor");
	else NamesBox_TeamStatus->SetName("Home");
}


void UTeamLineup::SetTeamName(const FString& NewTeamName){TeamName = NewTeamName;}
TArray<URacerStatsLine*>& UTeamLineup::GetRacers(){return Racers;}


#include "UI/League/Programm/TeamLineup.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Data/TeamData/TeamsDataAsset.h"
#include "UI/BaseClasses/NamesBox.h"
#include "UI/BaseClasses/NumbersBox.h"
#include "UI/League/Programm/RacerStatsLine.h"


void UTeamLineup::NativeConstruct()
{
	Super::NativeConstruct();
	SetTeam();
	CreateRacerStatLines();
	FillTeamLineups();
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
	if (!TeamLineupsDataAsset) return;
	for (const auto& Racer : Racers)
	{
		//if (IsVisitorTeam) FillTeam(Racer, TeamLineupsDataAsset->Team_Sparta);
		//else FillTeam(Racer, TeamLineupsDataAsset->Team_Lokomotive);
	}
}


void UTeamLineup::FillTeam(URacerStatsLine* const& Racer,  TArray<FRacerStats> TeamData)
{
	for (const auto& RacerData : TeamData)
	{
		//Racer->AddOption(RacerData.Name);
	}
}


void UTeamLineup::SetTeam()
{
	if (IsVisitorTeam)
	{
		NamesBox_TeamStatus->SetName("Visitor");
		NamesBox_TeamName->SetName("Sparta Wroclaw");
	}
	else
	{
		NamesBox_TeamStatus->SetName("Home");
		NamesBox_TeamName->SetName("Lokomotive Daugavpils");
	}
}


void UTeamLineup::UpdateTeamPoints(int NewPoints)
{
	NumbersBox_TeamPoints->AddNumber(NewPoints);
}


TArray<URacerStatsLine*>& UTeamLineup::GetRacers(){return Racers;}
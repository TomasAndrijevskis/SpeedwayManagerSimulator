
#include "UI/League/Program/NominatedRaceLine.h"
#include "Managers/TeamManager.h"
#include "UI/BaseClasses/ChooseBox.h"
#include "UI/BaseClasses/NumbersBox.h"


void UNominatedRaceLine::SetRaceLineData(const FRaceLineData& NewRaceLineData, const TArray<UTeamManager*>& TeamManagers)
{
	RaceLineData = NewRaceLineData;
	for (const auto& Manager : TeamManagers)
	{
		if (RaceLineData.IsVisitor() == Manager->IsVisitor()) TeamManager = Manager;
	}
	NumbersBox_RacerNumber->SetColour(RaceLineData.HelmetColour);
	FillOptions();
}


void UNominatedRaceLine::FillOptions()
{
	TeamManager->ForEachRacerInLineup([this](int ID, const FRacerData& Data)
	{
		AddOption(Data.Name);
	});
}


void UNominatedRaceLine::AddOption(const FString& RacerName)
{
	ChooseBox_ChooseRacer->AddOption(RacerName);
}


void UNominatedRaceLine::SetRacerID(int NewRacerID)
{
	RacerID = NewRacerID;
}


void UNominatedRaceLine::SetRaceLineID(int NewID){RaceLineID = NewID;}
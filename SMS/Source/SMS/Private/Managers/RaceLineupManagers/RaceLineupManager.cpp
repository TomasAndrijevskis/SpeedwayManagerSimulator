
#include "Managers/RaceLineupManagers/RaceLineupManager.h"
#include "Managers/RacerMatchManager.h"
#include "UI/BaseClasses/RaceLine_Base.h"


void URaceLineupManager::InitializeManager()
{
	BindDelegates();
}



void URaceLineupManager::AddRaceLine(URaceLine_Base* NewRaceLine)
{
	RaceLines.Add(NewRaceLine);
}


void URaceLineupManager::AssignRacerToRace(URacerMatchManager* RacerManager)
{
	for (const auto& RaceLine : RaceLines)
	{
		if (RaceLine->GetRacerNumber() == RacerManager->GetRacerNumber())
			RaceLine->SetRacerData(RacerManager, false);
	}
}
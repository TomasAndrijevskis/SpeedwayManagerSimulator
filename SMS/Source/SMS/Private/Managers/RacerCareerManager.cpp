
#include "Managers/RacerCareerManager.h"


void URacerCareerManager::Initialize(const FRacerData& RacerData)
{
	Data = RacerData;
}


FRacerData& URacerCareerManager::GetRacerData(){return Data;}

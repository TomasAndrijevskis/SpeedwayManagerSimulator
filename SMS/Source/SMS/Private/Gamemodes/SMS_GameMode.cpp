
#include "Gamemodes/SMS_GameMode.h"
#include <Managers/PointsManager.h>


void ASMS_GameMode::BeginPlay()
{
	Super::BeginPlay();
	PointsManager = NewObject<UPointsManager>(this);
}


UPointsManager* ASMS_GameMode::GetPointsManager()const{return PointsManager;}
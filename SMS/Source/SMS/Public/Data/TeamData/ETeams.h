
#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum ETeams
{
	Nothing UMETA(DisplayName = "No team"),
	LD UMETA(DisplayName = "Lokomotive Daugavpils"),
	SW UMETA(DisplayName = "Sparta Wroclaw"),
	WCz UMETA(DisplayName = "Włókniarz Częstochowa"),
	UT UMETA(DisplayName = "Unibax Toruń"),
	ML UMETA(DisplayName = "Motor Lublin"),
	SG UMETA(DisplayName = "Stal Gorzów"),
};
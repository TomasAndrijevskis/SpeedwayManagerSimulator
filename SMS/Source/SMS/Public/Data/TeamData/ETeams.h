
#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class ETeams : uint8
{
	Nothing = 0 UMETA(DisplayName = "No team"),
	LD = 1 UMETA(DisplayName = "Lokomotive Daugavpils"),
	SW = 2 UMETA(DisplayName = "Sparta Wroclaw"),
	WCz = 3 UMETA(DisplayName = "Włókniarz Częstochowa"),
	UT = 4 UMETA(DisplayName = "Unibax Toruń"),
	ML = 5 UMETA(DisplayName = "Motor Lublin"),
	SGo = 6 UMETA(DisplayName = "Stal Gorzów"),
	RR = 7 UMETA(DisplayName = "Row Rybnik"),
	UL = 8 UMETA(DisplayName = "Unia Leszno"),
	OL = 9 UMETA(DisplayName = "Orzeł Lódz"),
	WG = 10 UMETA(DisplayName = "Wybrzeże Gdańsk"),
	FZ = 11 UMETA(DisplayName = "Falubaz Zielona Góra"),
	SGn = 12 UMETA(DisplayName = "Start Gniezno"),
};

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
	SGo UMETA(DisplayName = "Stal Gorzów"),
	RR UMETA(DisplayName = "Row Rybnik"),
	UL UMETA(DisplayName = "Unia Leszno"),
	OL UMETA(DisplayName = "Orzeł Lódz"),
	WG UMETA(DisplayName = "Wybrzeże Gdańsk"),
	FZ UMETA(DisplayName = "Falubaz Zielona Góra"),
	SGn UMETA(DisplayName = "Start Gniezno"),
};
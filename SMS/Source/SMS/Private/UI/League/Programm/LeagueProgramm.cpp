
#include "UI/League/Programm/LeagueProgramm.h"
#include "Components/BackgroundBlur.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "UI/League/Programm/Race.h"
#include "UI/League/Programm/RacerStatsLine.h"
#include "UI/League/Programm/TeamLineup.h"


void ULeagueProgramm::NativeConstruct()
{
	Super::NativeConstruct();
	Button_SimulateRace->OnClicked.AddUniqueDynamic(this, &ULeagueProgramm::SimulateRace);
	Button_ShowTeams->OnClicked.AddUniqueDynamic(this, &ULeagueProgramm::ShowTeams);
	CreateRacesArray();
	BindDelegates();
	SetRaceID();
	ShowTeams();
}


void ULeagueProgramm::CreateRacesArray()
{
	Races.Add(Race_One);
	Races.Add(Race_Two);
	Races.Add(Race_Three);
	Races.Add(Race_Four);
	Races.Add(Race_Five);
	Races.Add(Race_Six);
	Races.Add(Race_Seven);
	Races.Add(Race_Eight);
	Races.Add(Race_Nine);
	Races.Add(Race_Ten);
	Races.Add(Race_Eleven);
	Races.Add(Race_Twelve);
	Races.Add(Race_Thirteen);
	Races.Add(Race_Fourteen);
	Races.Add(Race_Fifteen);
}


void ULeagueProgramm::BindDelegates()
{
	for (const auto& Racer : TeamLineup_HomeTeam->GetRacers())
	{
		Racer->OnRacerChosenDelegate.AddUObject(this, &ULeagueProgramm::FillRacers);
	}
}


void ULeagueProgramm::ShowTeams()
{
	if (VB_Teams->IsVisible())
	{
		VB_Teams->SetVisibility(ESlateVisibility::Hidden);
		BackgroundBlur->SetBlurStrength(0);
	}
	else
	{
		VB_Teams->SetVisibility(ESlateVisibility::Visible);
		BackgroundBlur->SetBlurStrength(15.f);
	}
}


void ULeagueProgramm::FillRacers(FString Name, int Id)
{
	for (const auto& Race : Races)
	{
		Race->AssignRacerToRace(Name, Id);
	}
}


void ULeagueProgramm::SetRaceID()
{
	int RaceID = 1;
	for (const auto& Race : Races)
	{
		Race->SetRaceID(RaceID);
		RaceID++;
	}
	
}


void ULeagueProgramm::SimulateRace()
{
	for (const auto& Race : Races)
	{
		Race->SimulateRace();
	}
}

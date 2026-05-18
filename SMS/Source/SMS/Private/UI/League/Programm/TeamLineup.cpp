
#include "UI/League/Programm/TeamLineup.h"
#include "UI/League/Programm/RacerStatsLine.h"


void UTeamLineup::NativeConstruct()
{
	Super::NativeConstruct();
	Racers.Add(RacerStatsLine_First);
	Racers.Add(RacerStatsLine_Second);
	Racers.Add(RacerStatsLine_Third);
	Racers.Add(RacerStatsLine_Fourth);
	Racers.Add(RacerStatsLine_Fifth);
	Racers.Add(RacerStatsLine_Sixth);
	SetRacerID();
}


void UTeamLineup::SetRacerID()
{
	int Id = 1;
	for (const auto& Racer : Racers)
	{
		Racer->SetID(Id);
		Id++;
	}
}


TArray<URacerStatsLine*>& UTeamLineup::GetRacers(){return Racers;}
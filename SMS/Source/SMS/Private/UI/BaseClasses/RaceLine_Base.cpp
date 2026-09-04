
#include "UI/BaseClasses/RaceLine_Base.h"
#include "Managers/RacerManager.h"
#include "UI/BaseClasses/NumbersBox.h"


void URaceLine_Base::NativeConstruct()
{
	Super::NativeConstruct();
	InitializeWidget();
}


void URaceLine_Base::SetRaceLineData(const FRaceLineData& NewRaceLineData)
{
	RaceLineData = NewRaceLineData;
	SetRacerNumber(RaceLineData.RacerID);
	NumbersBox_RacerNumber->SetColour(NewRaceLineData.HelmetColour);
}


void URaceLine_Base::BindManagersDelegates()
{
	if (RacerManager) OnRaceSimulatedDelegate.AddUObject(RacerManager, &URacerManager::CalculateRating);
}


void URaceLine_Base::SetRacerNumber(int32 NewRacerNumber)
{
	RacerNumber = NewRacerNumber;
	if (RacerNumber != 0) NumbersBox_RacerNumber->SetText(RacerNumber);
}


void URaceLine_Base::SetPointsPerRace(const FString& NewPoints)
{
	NumbersBox_PointsPerRace->SetText(NewPoints);
}


void URaceLine_Base::ChangeLineStatus(bool bIsActive)
{
	SetIsEnabled(bIsActive);
}


void URaceLine_Base::SetRaceLineID(int32 NewID){RaceLineID = NewID;}
int32 URaceLine_Base::GetRaceLineID()const{return RaceLineID;}
int32 URaceLine_Base::GetRacerNumber()const{return RacerNumber;}
int32 URaceLine_Base::GetTieBreaker()const{return RacerManager->GetTieBreaker();}
int32 URaceLine_Base::GetRacerRating()const{return RacerManager->GetCurrentRaceRating();}
int32 URaceLine_Base::GetPointsPerRace()const{return NumbersBox_PointsPerRace->GetNumber();}
URacerManager* URaceLine_Base::GetRacerManager()const{return RacerManager;}
FRaceLineData& URaceLine_Base::GetRaceLineData(){return RaceLineData;}
bool URaceLine_Base::IsRacerSet() const{return bIsRacerSet;}
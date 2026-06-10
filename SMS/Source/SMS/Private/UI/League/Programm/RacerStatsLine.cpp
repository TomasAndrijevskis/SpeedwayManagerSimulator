
#include "SMS/Public/UI/League/Program/RacerStatsLine.h"
#include "Components/HorizontalBox.h"
#include "Managers/TeamRostersManager.h"
#include "UI/BaseClasses/ChooseBox.h"
#include "UI/BaseClasses/NumbersBox.h"


void URacerStatsLine::NativeConstruct()
{
	Super::NativeConstruct();
	BindDelegates();
	OnValueAddRequestDelegate.AddUObject(this, &URacerStatsLine::AddPoints);
	ChooseBox_Racer->OnSelectionChangedDelegate.AddUObject(this, &URacerStatsLine::OnRacerChosen);
}


void URacerStatsLine::Init(UTeamRostersManager* NewTeamRosterManager)
{
	if (!NewTeamRosterManager) return;
	TeamRosterManager = NewTeamRosterManager;
}


void URacerStatsLine::BindDelegates()
{
	if (!TeamRosterManager) return;
	OnRacerChosenDelegate.AddUObject(TeamRosterManager, &UTeamRostersManager::AddRacer);
}


void URacerStatsLine::AddOption(const FString& NewOption)
{
	ChooseBox_Racer->AddOption(NewOption);
}


void URacerStatsLine::AddPoints(const FString& NewPoints)
{
	if (!CanAddNewPointBox()) return;
	RacerPoints.Add(NewPoints);
	CreateNewPointsBox(RacerPoints.Last());
}


void URacerStatsLine::CreateNewPointsBox(const FString& Points)
{
	if (!PointsBoxClass) return;
	UNumbersBox* NewNumbersBox = Cast<UNumbersBox>(CreateWidget(this, PointsBoxClass));
	if (!NewNumbersBox) return;
	NewNumbersBox->SetText(Points);
	HB_Points->AddChild(NewNumbersBox);
	UpdateOverallPoints(CountOverallPoints());
	OnPointsUpdatedDelegate.Broadcast(FCString::Atoi(*Points));
}


int URacerStatsLine::CountOverallPoints()
{
	if (!HB_Points->HasAnyChildren()) return 0;
	int sum = 0;
	for (const auto& Element : HB_Points->GetAllChildren())
	{
		int Number = Cast<UNumbersBox>(Element)->GetNumber();
		sum += Number;
	}
	return sum;
}


bool URacerStatsLine::CanAddNewPointBox() const
{
	if (HB_Points->GetChildrenCount() < MaxRacesAmount) return true;
	return false;
}


void URacerStatsLine::OnRacerChosen(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	RacerName = SelectedItem;
	OnRacerChosenDelegate.Broadcast(SelectedItem, ID);
}


void URacerStatsLine::UpdateOverallPoints(int Points)
{
	NumbersBox_OverallPoints->SetText(Points);
}


void URacerStatsLine::SetID(int NewID)
{
	ID = NewID;
	NumbersBox_RiderNumber->SetText(ID);
}


int URacerStatsLine::GetID() const{return ID;}
FString URacerStatsLine::GetRacerName() const{return RacerName;}
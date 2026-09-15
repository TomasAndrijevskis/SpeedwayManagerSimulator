
#include "UI/BaseClasses/RacerStatsLine_Base.h"
#include "Components/HorizontalBox.h"
#include "Managers/RacerMatchManager.h"
#include "Subsystems/RulesSubsystem.h"
#include "UI/BaseClasses/NumbersBox.h"


void URacerStatsLine_Base::InitializeManagers(URacerMatchManager* RacerManagerRef)
{
	UE_LOG(LogTemp, Warning, TEXT("ULeague_RacerStatsLine::InitializeManagers"));
	RacerManager = RacerManagerRef;
	BindDelegates();
}


void URacerStatsLine_Base::BindDelegates()
{
	if (!RacerManager) return;
	RacerManager->OnPointsAddedDelegate.AddUObject(this, &URacerStatsLine_Base::CreateNewPointsBox);
}


void URacerStatsLine_Base::CreateNewPointsBox(const ERaceResults& RaceResult, bool AddBonus)
{
	if (!PointsBoxClass || !RacerManager) return;
	if (URulesSubsystem* Rules = GetWorld()->GetGameInstance()->GetSubsystem<URulesSubsystem>())
	{
		UNumbersBox* NewNumbersBox = Cast<UNumbersBox>(CreateWidget(this, PointsBoxClass));
		if (!NewNumbersBox) return;
		FString Points = Rules->GetRaceResultText(RaceResult);
		if (AddBonus) NewNumbersBox->SetText(Points + "*");
		else NewNumbersBox->SetText(Points);
		HB_Points->AddChild(NewNumbersBox);
		UpdateOverallPoints(RacerManager->CountOverallPoints(), RacerManager->GetBonusAmount());
	}
}


void URacerStatsLine_Base::UpdateOverallPoints(int32 Points, int32 Bonus)
{
	const FString NewText = FString::Printf(TEXT("%d+%d"), Points, Bonus);
	if (Bonus > 0) NumbersBox_OverallPoints->SetText(NewText);
	else NumbersBox_OverallPoints->SetText(Points);
}


void URacerStatsLine_Base::SetID(int32 NewID)
{
	RacerStatsLineID = NewID;
	NumbersBox_RacerNumber->SetText(RacerStatsLineID);
}


int32 URacerStatsLine_Base::GetID() const{return RacerStatsLineID;}
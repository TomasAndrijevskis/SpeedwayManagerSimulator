
#include "SMS/Public/UI/League/Program/League_RacerStatsLine.h"
#include "Components/HorizontalBox.h"
#include "Managers/RacerMatchManager.h"
#include "Subsystems/RulesSubsystem.h"
#include "UI/BaseClasses/ChooseBox.h" 
#include "UI/BaseClasses/NumbersBox.h"


void ULeague_RacerStatsLine::NativeConstruct()
{
	Super::NativeConstruct();
	ChooseBox_Racer->OnSelectionChangedDelegate.AddUObject(this, &ULeague_RacerStatsLine::OnRacerChosen);
}


void ULeague_RacerStatsLine::InitializeManagers(URacerMatchManager* RacerManagerRef)
{
	UE_LOG(LogTemp, Warning, TEXT("ULeague_RacerStatsLine::InitializeManagers"));
	RacerManager = RacerManagerRef;
	BindDelegates();
}


void ULeague_RacerStatsLine::BindDelegates()
{
	if (!RacerManager) return;
	RacerManager->OnPointsAddedDelegate.AddUObject(this, &ULeague_RacerStatsLine::CreateNewPointsBox);
}


void ULeague_RacerStatsLine::AddOption(const TObjectPtr<URacerMatchManager>& NewRacerManager)
{
	if (NewRacerManager)
	{
		Racers.Add(NewRacerManager);
		ChooseBox_Racer->AddOption(NewRacerManager->GetRacerName());
	}
	else ChooseBox_Racer->AddOption("");
}


void ULeague_RacerStatsLine::RemoveOption(const FString& Option)
{
	ChooseBox_Racer->RemoveOption(Option);
}


void ULeague_RacerStatsLine::CreateNewPointsBox(const ERaceResults& RaceResult, bool AddBonus)
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


void ULeague_RacerStatsLine::OnRacerChosen(FString SelectedOption, ESelectInfo::Type SelectionType)
{
	if (PreviousOption == "")
	{
		PreviousOption = SelectedOption;
		TObjectPtr<URacerMatchManager> EmptyData = nullptr;
		OnSelectedOptionChangedDelegate.Broadcast(this, SelectedOption, EmptyData);
	}
	else
	{
		for (const auto& Racer : Racers)
		{
			if (Racer->GetRacerName() == PreviousOption)
			{
				SelectedData = Racer; break;
			}
		}
		OnSelectedOptionChangedDelegate.Broadcast(this, SelectedOption, SelectedData);
		PreviousOption = SelectedOption;
	}
	OnRacerSelectedDelegate.Broadcast(SelectedOption, RacerStatsLineID);
}


void ULeague_RacerStatsLine::ChooseRandomOption()
{
	if (ChooseBox_Racer->GetSelectedOption() != "") return;
	int OptionsAmount = ChooseBox_Racer->GetNumberOfOptions();
	int RandomOption = FMath::RandRange(0, OptionsAmount - 1);
	FString SelectedOption = ChooseBox_Racer->GetOptionAtIndex(RandomOption);
	if (SelectedOption == "")
	{
		if (ChooseBox_Racer->AnyOptionsLeft()) ChooseRandomOption();
	}
	else
	{
		ChooseBox_Racer->SetRandomOption(SelectedOption);
		OnRacerSelectedDelegate.Broadcast(SelectedOption, RacerStatsLineID);
	}
}


void ULeague_RacerStatsLine::LockRacer()
{
	ChooseBox_Racer->DisableChooseBox();
}


void ULeague_RacerStatsLine::UpdateOverallPoints(int32 Points, int32 Bonus)
{
	const FString NewText = FString::Printf(TEXT("%d+%d"), Points, Bonus);
	if (Bonus > 0) NumbersBox_OverallPoints->SetText(NewText);
	else NumbersBox_OverallPoints->SetText(Points);
}


void ULeague_RacerStatsLine::SetID(int32 NewID)
{
	RacerStatsLineID = NewID;
	NumbersBox_RacerNumber->SetText(RacerStatsLineID);
}


int32 ULeague_RacerStatsLine::GetID() const{return RacerStatsLineID;}
int32 ULeague_RacerStatsLine::GetNumberOfOptions() const{return ChooseBox_Racer->GetNumberOfOptions();}
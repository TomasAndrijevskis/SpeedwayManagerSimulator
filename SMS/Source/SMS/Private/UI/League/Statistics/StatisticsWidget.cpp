
#include "UI/League/Statistics/StatisticsWidget.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Subsystems/OverallStatsSubsystem.h"
#include "UI/League/Statistics/StatisticsLine.h"


void UStatisticsWidget::InitializeStatisticsWidget()
{
	if (UOverallStatsSubsystem* Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UOverallStatsSubsystem>())
	{
		for (const auto& RacerStats : Subsystem->RacerStatistics)
		{
			for (const auto& ExistingLine : ExistingStatisticsLines)
			{
				if (ExistingLine->GetRacerID() == RacerStats.RacerID)
				{
					UpdateExistingStatisticsLine();
					break;
				}
			}
			CreateNewStatisticsLine(RacerStats.RacerID);
		}
	}
}


void UStatisticsWidget::CreateNewStatisticsLine(int32 ID)
{
	UStatisticsLine* NewStatisticsLine = CreateWidget<UStatisticsLine>(this, StatisticsLineClass);
	if (!NewStatisticsLine) return;
	NewStatisticsLine->InitializeLine(ID);
	VerticalBox_StatisticsBox->AddChild(NewStatisticsLine);
}


void UStatisticsWidget::UpdateExistingStatisticsLine()
{
	UE_LOG(LogTemp, Warning, TEXT("Found, needs to be updated"));
}


void UStatisticsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button_Exit->OnClicked.AddUniqueDynamic(this, &UStatisticsWidget::RemoveWidget);
}


void UStatisticsWidget::RemoveWidget()
{
	this->RemoveFromParent();
}

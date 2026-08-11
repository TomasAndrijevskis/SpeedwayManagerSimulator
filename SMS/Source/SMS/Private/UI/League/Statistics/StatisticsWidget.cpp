
#include "UI/League/Statistics/StatisticsWidget.h"
#include "Components/Button.h"
#include "Components/WrapBox.h"
#include "Subsystems/OverallStatsSubsystem.h"
#include "UI/League/Statistics/StatisticsLine.h"


void UStatisticsWidget::InitializeStatisticsWidget()
{
	if (UOverallStatsSubsystem* Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UOverallStatsSubsystem>())
	{
		for (const auto& RacerStats : Subsystem->GetRacerStatistics())
		{
			StatisticsLines.Add(CreateNewStatisticsLine(RacerStats));
		}
		SortLines();
	}
	int32 Rank = 1;
	for (const auto& Line : StatisticsLines)
	{
		Line->SetRank(Rank);
		WrapBox_StatisticsBox->AddChildToWrapBox(Line);
		Rank++;
	}
}


void UStatisticsWidget::SortLines()
{
	StatisticsLines.Sort([](const UStatisticsLine& L1, const UStatisticsLine& L2)
	{
		return L1.GetRacerAverage() > L2.GetRacerAverage();
	});
}


UStatisticsLine* UStatisticsWidget::CreateNewStatisticsLine(const FRacerStatistics& Data)
{
	UStatisticsLine* NewStatisticsLine = CreateWidget<UStatisticsLine>(this, StatisticsLineClass);
	if (!NewStatisticsLine) return nullptr;
	NewStatisticsLine->InitializeLine(Data);
	return NewStatisticsLine;
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

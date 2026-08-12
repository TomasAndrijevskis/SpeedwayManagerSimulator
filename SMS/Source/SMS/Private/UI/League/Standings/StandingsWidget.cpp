
#include "UI/League/Standings/StandingsWidget.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Subsystems/StandingsSubsystem.h"
#include "UI/League/Standings/StandingsLine.h"


void UStandingsWidget::InitializeStandingsWidget()
{
	Button_Exit->OnClicked.AddUniqueDynamic(this, &UStandingsWidget::RemoveWidget);
	if (UStandingsSubsystem* Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UStandingsSubsystem>())
	{
		for (const auto& Team : Subsystem->GetTeamStatistics())
		{
			StandingsLines.Add(CreateNewStandingsLine(Team));
		}
	}
	SortLines();
	int32 Rank = 1;
	for (const auto& Line : StandingsLines)
	{
		Line->SetRank(Rank);
		VerticalBox_Standings->AddChild(Line);
		Rank++;
	}
}


UStandingsLine* UStandingsWidget::CreateNewStandingsLine(const FTeamStatistics& TeamStats)
{
	if (!StandingsLineClass) return nullptr;
	UStandingsLine* NewStandingsLine = CreateWidget<UStandingsLine>(this, StandingsLineClass);
	if (!NewStandingsLine) return nullptr;
	NewStandingsLine->InitializeStandingsLine(TeamStats);
	return NewStandingsLine;
}


void UStandingsWidget::SortLines()
{
	StandingsLines.Sort([](const UStandingsLine& L1, const UStandingsLine& L2)
	{
		if (L1.GetTeamPoints() != L2.GetTeamPoints())
		{
			return L1.GetTeamPoints() > L2.GetTeamPoints();
		}
		if (L1.GetWins() != L2.GetWins())
		{
			return L1.GetWins() > L2.GetWins();
		}
		if (L1.GetMatchesAmount() != L2.GetMatchesAmount())
		{
			return L1.GetMatchesAmount() > L2.GetMatchesAmount();
		}
		return L1.GetDifference() > L2.GetDifference();
	});
}

void UStandingsWidget::RemoveWidget()
{
	this->RemoveFromParent();
}


#include "UI/GP/Program/GP_Lineup.h"
#include "Components/VerticalBox.h"
#include "Managers/RacerMatchManager.h"
#include "Rules/GP_Rules.h"
#include "Subsystems/MatchManagerSubsystem.h"
#include "UI/GP/GP_RacerStatsLine.h"


void UGP_Lineup::NativeConstruct()
{
	Super::NativeConstruct();
	CreateRacerStatsLines();
}


void UGP_Lineup::CreateRacerStatsLines()
{
	if (!RacerStatsLineClass) return;
	if (UMatchManagerSubsystem* MatchManagerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMatchManagerSubsystem>())
	{
		if (UGP_Rules* GPRules = Cast<UGP_Rules>(MatchManagerSubsystem->GetCompetitionRules()))
		{
			int i = 1;
			int Amount = GPRules->GetRacers().Num();
			for (const auto& Racer : GPRules->GetRacers())
			{
				if (UGP_RacerStatsLine* RacerStatsLine = CreateRacerStatsLine(Racer, i))
				{
					FillLineup(RacerStatsLine, i, Amount);
					RacerStatsLines.Add(RacerStatsLine);
					i++;
				}
			}
		}
	}
}


void UGP_Lineup::FillLineup(UGP_RacerStatsLine* RacerStatsLine, int32 ID, int32 Amount)
{
	if (ID <= Amount / 2) VB_TopRacers->AddChild(RacerStatsLine);
	else VB_BottomRacers->AddChild(RacerStatsLine);
}


UGP_RacerStatsLine* UGP_Lineup::CreateRacerStatsLine(const TObjectPtr<URacerMatchManager>& RacerManager, int Position)
{
	if (UGP_RacerStatsLine* RacerStatsLine = Cast<UGP_RacerStatsLine>(CreateWidget(this, RacerStatsLineClass)))
	{
		RacerStatsLine->SetRacerStatsLineID(RacerManager->GetRacerNumber());
		RacerStatsLine->SetRacerName(RacerManager->GetRacerName());
		RacerStatsLine->InitializeManagers(RacerManager);
		RacerStatsLine->UpdateRacerPosition(Position);
		return RacerStatsLine;
	}
	return nullptr;
}


void UGP_Lineup::SortLines()
{
	RacerStatsLines.Sort([](const auto& L1, const auto& L2)
	{
		URacerMatchManager* MatchManager1 = L1.GetRacerManager();
		URacerMatchManager* MatchManager2 = L2.GetRacerManager();
		if (MatchManager1->CountOverallPoints() == MatchManager2->CountOverallPoints())
		{
			return MatchManager1->GetAmountOfWins() > MatchManager2->GetAmountOfWins();
		}
		return MatchManager1->CountOverallPoints() > MatchManager2->CountOverallPoints();
	});
	VB_TopRacers->ClearChildren();
	VB_BottomRacers->ClearChildren();
	int i = 1;
	int Amount = RacerStatsLines.Num();
	for (const auto& Line : RacerStatsLines)
	{
		FillLineup(Line, i, Amount);
		Line->UpdateRacerPosition(i);
		i++;
	}
}
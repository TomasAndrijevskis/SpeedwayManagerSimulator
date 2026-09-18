
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
			int32 Position = 0;
			int32 RacersCount = GPRules->GetRacers().Num();
			for (const auto& Racer : GPRules->GetRacers())
			{
				if (UGP_RacerStatsLine* RacerStatsLine = CreateRacerStatsLine(Racer, Position))
				{
					AddRacerStatsLine(RacerStatsLine, Position, RacersCount);
					RacerStatsLines.Add(RacerStatsLine);
					Position++;
				}
			}
		}
	}
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
	if (UMatchManagerSubsystem* MatchManagerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMatchManagerSubsystem>())
	{
		if (UGP_Rules* GPRules = Cast<UGP_Rules>(MatchManagerSubsystem->GetCompetitionRules()))
		{
			GPRules->SortRacers();
			int32 Position = 0;
			int32 RacersCount = GPRules->GetRacers().Num() - 1;
			for (const auto& Racer : GPRules->GetRacers())
			{
				for (const auto& Line : RacerStatsLines)
				{
					if (Racer == Line->GetRacerManager())
					{
						MoveRacerStatsLine(Line, Position, RacersCount);
						Line->UpdateRacerPosition(Position);
						Position++;
					}
				}
			}
			VB_TopRacers->InvalidateLayoutAndVolatility();
			VB_BottomRacers->InvalidateLayoutAndVolatility();
		}
	}
}


void UGP_Lineup::MoveRacerStatsLine(UGP_RacerStatsLine* RacerStatsLine, int32 Position, int32 RacersCount)
{
	UE_LOG(LogTemp, Error, TEXT("=============================="));
	UE_LOG(LogTemp, Display, TEXT("%s"), *RacerStatsLine->GetRacerManager()->GetRacerName());
	UE_LOG(LogTemp, Display, TEXT("position %i"), Position);
	if (Position <= RacersCount / 2)
	{
		if (VB_TopRacers->HasChild(RacerStatsLine))
		{
			UE_LOG(LogTemp, Warning, TEXT("current index %i"), VB_TopRacers->GetChildIndex(RacerStatsLine));
			VB_TopRacers->InsertChildAt(Position, RacerStatsLine);
			UE_LOG(LogTemp, Warning, TEXT("new index %i"), VB_TopRacers->GetChildIndex(RacerStatsLine));
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("move to top half"));
			VB_BottomRacers->RemoveChild(RacerStatsLine);
			VB_TopRacers->AddChild(RacerStatsLine);
		}
	}
	else
	{
		if (VB_BottomRacers->HasChild(RacerStatsLine))
		{
			UE_LOG(LogTemp, Warning, TEXT("current index %i"), VB_BottomRacers->GetChildIndex(RacerStatsLine));
			VB_BottomRacers->InsertChildAt(Position - RacersCount/2, RacerStatsLine);
			UE_LOG(LogTemp, Warning, TEXT("new index %i"), VB_BottomRacers->GetChildIndex(RacerStatsLine));
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("move to bottom half"));
			VB_TopRacers->RemoveChild(RacerStatsLine);
			VB_BottomRacers->AddChild(RacerStatsLine);
		}
	}
}


void UGP_Lineup::AddRacerStatsLine(UGP_RacerStatsLine* RacerStatsLine, int32 Position, int32 Amount)
{

	if (Position <= (Amount / 2 ) - 1) VB_TopRacers->AddChild(RacerStatsLine);
	else VB_BottomRacers->AddChild(RacerStatsLine);
}

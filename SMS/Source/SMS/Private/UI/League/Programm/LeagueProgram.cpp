
#include "SMS/Public/UI/League/Program/LeagueProgram.h"
#include "Components/BackgroundBlur.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/VerticalBox.h"
#include "SMS/Public/UI/League/Program/Race.h"
#include "SMS/Public/UI/League/Program/RacerStatsLine.h"
#include "SMS/Public/UI/League/Program/TeamLineup.h"


void ULeagueProgram::NativeConstruct()
{
	Super::NativeConstruct();
	Button_SimulateRace->OnClicked.AddUniqueDynamic(this, &ULeagueProgram::SimulateRace);
	Button_ShowTeams->OnClicked.AddUniqueDynamic(this, &ULeagueProgram::ShowTeams);
	CreateRaces();
	BindDelegates();
	//ShowTeams();
}


void ULeagueProgram::CreateTeam(bool IsVisitor, const FString& TeamName, const FTeamRosterData& TeamData)
{
	if (!TeamLineupClass) return;
	UTeamLineup* TeamLineup = CreateWidget<UTeamLineup>(this, TeamLineupClass);
	if (!TeamLineup) return;
	TeamLineup->SetIsVisitorTeam(IsVisitor);
	TeamLineup->SetTeamName(TeamName);
	VB_Teams->AddChild(TeamLineup);
	TeamLineups.Add(TeamLineup);
	//UE_LOG(LogTemp, Error, TEXT("%s"), *StaticEnum<ETeams>()->GetDisplayValueAsText(TeamData.TeamID).ToString())
	for (const auto& Team : TeamData.Racers)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Team);
	}
}


void ULeagueProgram::CreateRaces()
{
	FVector2d TempPosition = StartPosition;
	FAnchors StartAnchors(0.0f, 0.5f, 0.0f, 0.5f);
	FVector2d StartAlignment = FVector2d(0, 0);
	for (int i = 1; i <= AmountOfRaces; i++)
	{
		const float PositionOffset = 162.0f;
		const float Offset = 0.5f;
		URace* NewRace = CreateRace(StartAnchors, TempPosition, StartAlignment);
		if (NewRace)
		{
			NewRace->SetRaceID(i);
			if (i != 1) NewRace->ChangeRaceStatus(false);
			Races.Add(NewRace);
		}
		TempPosition.Y += PositionOffset;
		if (i % 5 == 0)
		{
			TempPosition = StartPosition;
			StartAnchors.Minimum.X += Offset;
			StartAnchors.Maximum.X += Offset;
			StartAlignment.X += Offset;
		}
	}
}


URace* ULeagueProgram::CreateRace(const FAnchors& Anchors, const FVector2d& Position, const FVector2d& Alignment)
{
	if (!RaceClass) return nullptr;
	URace* NewRace = CreateWidget<URace>(this, RaceClass);
	if (!NewRace) return nullptr;
	UCanvasPanelSlot* RaceSlot = CanvasPanel_Root->AddChildToCanvas(NewRace);
	if (RaceSlot)
	{
		RaceSlot->SetAnchors(Anchors);
		RaceSlot->SetPosition(Position);
		RaceSlot->SetAlignment(Alignment);
		RaceSlot->SetAutoSize(true);
	}
	return NewRace;
}


void ULeagueProgram::BindDelegates()
{
	for (const auto& TeamLineup : TeamLineups)
	{
		for (const auto& Racer : TeamLineup->GetRacers())
		{
			Racer->OnRacerChosenDelegate.AddUObject(this, &ULeagueProgram::FillRacers);
		}
	}
}


void ULeagueProgram::ShowTeams()
{
	if (VB_Teams->IsVisible())
	{
		VB_Teams->SetVisibility(ESlateVisibility::Hidden);
		BackgroundBlur->SetBlurStrength(0);
	}
	else
	{
		VB_Teams->SetVisibility(ESlateVisibility::Visible);
		BackgroundBlur->SetBlurStrength(15.f);
	}
}



void ULeagueProgram::FillRacers(FString Name, int Id)
{
	for (const auto& Race : Races)
	{
		Race->AssignRacerToRace(Name, Id);
	}
}


void ULeagueProgram::SimulateRace()
{
	if (CurrentRace < Races.Num())
	{
		Races[CurrentRace]->OnOverallScoreUpdatedDelegate.AddUObject(this, &ULeagueProgram::SetOverallPts);
		Races[CurrentRace]->OnRaceFinishedDelegate.AddUObject(this, &ULeagueProgram::OnRaceFinished);
		Races[CurrentRace]->SimulateRace();
		Races[CurrentRace]->OnOverallScoreUpdatedDelegate.Clear();
		CurrentRace++;
		if (CurrentRace < Races.Num()) Races[CurrentRace]->ChangeRaceStatus(true);
	}
}


void ULeagueProgram::OnRaceFinished(int ID, int NewPoints)
{
	//if (ID <= 6) AddRacerPoints(ID, NewPoints, TeamLineup_HomeTeam->GetRacers());
	//else AddRacerPoints(ID, NewPoints, TeamLineup_VisitorTeam->GetRacers());
}


void ULeagueProgram::AddRacerPoints(int ID, int NewPoints, TArray<URacerStatsLine*>& Racers)
{
	for (auto& Racer : Racers)
	{
		if (Racer->GetID() == ID) Racer->OnValueAddRequestDelegate.Broadcast(FString::FromInt(NewPoints));
	}
}


void ULeagueProgram::SetOverallPts(int AddHomePts, int AddVisitorPts)
{
	HomeOverallPts += AddHomePts;
	VisitorOverallPts += AddVisitorPts;
	Races[CurrentRace]->UpdateOverallScore(HomeOverallPts, VisitorOverallPts);
}
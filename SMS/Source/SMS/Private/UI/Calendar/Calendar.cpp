
#include "UI/Calendar/Calendar.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Data/Calendar/CalendarDataAsset.h"
#include "UI/League/Standings/StandingsWidget.h"
#include "UI/League/Statistics/StatisticsWidget.h"
#include "UI/Calendar/CalendarRound.h"
#include "UI/GP/Program/GP_Program.h"


void UCalendar::NativeConstruct()
{
	Super::NativeConstruct();
	CreateCalendarRounds();
	Button_OpenStatistics->OnClicked.AddUniqueDynamic(this, &UCalendar::CreateStatisticsWidget);
	Button_OpenStandings->OnClicked.AddUniqueDynamic(this, &UCalendar::CreateStandingsWidget);
	Button_StartGP->OnClicked.AddUniqueDynamic(this, &UCalendar::StartGP);
}


void UCalendar::CreateCalendarRounds()
{
	if (!CalendarDataAsset) return;
	for (const auto& Round : CalendarDataAsset->Rounds)
	{
		if (UCalendarRound* NewRound = CreateRound())
		{
			NewRound->SetRound(Round.Week);
			NewRound->CreateMatches(Round.Races);
			VB_Content->AddChildToVerticalBox(NewRound);
		}
	}
}


UCalendarRound* UCalendar::CreateRound()
{
	if (!CalendarRoundClass) return nullptr;
	UCalendarRound* NewRound = CreateWidget<UCalendarRound>(this, CalendarRoundClass);
	if (!NewRound) return nullptr;
	return NewRound;
}


void UCalendar::CreateStatisticsWidget()
{
	if (!StatisticsWidgetClass) return;
	UStatisticsWidget* Widget = CreateWidget<UStatisticsWidget>(this, StatisticsWidgetClass);
	if (!Widget) return;
	Widget->InitializeStatisticsWidget();
	Widget->AddToViewport(0);
}


void UCalendar::CreateStandingsWidget()
{
	if (!StandingsWidgetClass) return;
	UStandingsWidget* Widget = CreateWidget<UStandingsWidget>(this, StandingsWidgetClass);
	if (!Widget) return;
	Widget->InitializeStandingsWidget();
	Widget->AddToViewport(0);
}


void UCalendar::StartGP()
{
	if (!ProgramClass) return;
	UGPProgram* Program = Cast<UGPProgram>(CreateWidget(this, ProgramClass));
	if (!Program) return;
	Program->AddToViewport(1);
}

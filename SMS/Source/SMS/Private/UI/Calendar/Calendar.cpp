
#include "UI/Calendar/Calendar.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Data/Calendar/CalendarDataAsset.h"
#include "Data/Calendar/MatchID.h"
#include "Subsystems/CalendarSubsystem.h"
#include "UI/League/Standings/StandingsWidget.h"
#include "UI/League/Statistics/StatisticsWidget.h"
#include "UI/Calendar/CalendarWeek.h"


void UCalendar::NativeConstruct()
{
	Super::NativeConstruct();
	CreateCalendarWeeks();
	Button_OpenStatistics->OnClicked.AddUniqueDynamic(this, &UCalendar::CreateStatisticsWidget);
	Button_OpenStandings->OnClicked.AddUniqueDynamic(this, &UCalendar::CreateStandingsWidget);
}


void UCalendar::CreateCalendarWeeks()
{
	if (!CalendarDataAsset) return;
	if (UCalendarSubsystem* Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UCalendarSubsystem>())
	{
		for (const auto& Week : CalendarDataAsset->Weeks)
		{
			if (UCalendarWeek* NewWeek = CreateWeek())
			{
				FMatchData MatchData;
				MatchData.MatchID.Season = Subsystem->GetCurrentSeason();
				MatchData.MatchID.Week = Week.Key;
				MatchData.MatchID.WeekMatchNumber = 1;
				switch (Week.Value.CompetitionType)
				{
				case ECompetitionType::League:
					MatchData.CompetitionType = ECompetitionType::League;
					NewWeek->CreateMatches(Week.Value.LeagueMatches.TeamPairs, MatchData);
					break;
				case ECompetitionType::GP:
					MatchData.CompetitionType = ECompetitionType::GP;
					NewWeek->CreateMatch(Week.Value.GPMatch.Location, Week.Value.GPMatch.Round, MatchData);
					break;
				case ECompetitionType::JGP:
					break;
				case ECompetitionType::GPCH:
					break;
				case ECompetitionType::SWC:
					break;
				case ECompetitionType::SON:
					break;
				default: break;
				}
				VB_Content->AddChildToVerticalBox(NewWeek);
			}
		}
		Subsystem->OnWeekChangedDelegate.Broadcast(Subsystem->GetCurrentWeek());
	}
}


UCalendarWeek* UCalendar::CreateWeek()
{
	if (!CalendarWeekClass) return nullptr;
	UCalendarWeek* NewWeek = CreateWidget<UCalendarWeek>(this, CalendarWeekClass);
	if (!NewWeek) return nullptr;
	return NewWeek;
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
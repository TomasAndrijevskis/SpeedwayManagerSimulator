
#include "UI/BaseClasses/CalendarLine_Base.h"
#include "Components/Button.h"
#include "Subsystems/CalendarSubsystem.h"
#include "UI/BaseClasses/NamesBox.h"


void UCalendarLine_Base::NativeConstruct()
{
	Super::NativeConstruct();
	BindDelegates();
}


void UCalendarLine_Base::BindDelegates()
{
	Button_StartMatch->OnClicked.AddUniqueDynamic(this, &UCalendarLine_Base::StartMatch);
	if (UCalendarSubsystem* Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UCalendarSubsystem>())
	{
		WeekChangedHandle = Subsystem->OnWeekChangedDelegate.AddUObject(this, &UCalendarLine_Base::ChangeLineStatus);
	}
}


void UCalendarLine_Base::OnMatchEnded()
{
	Button_StartMatch->OnClicked.Clear();
	Button_StartMatch->SetIsEnabled(false);
	if (UCalendarSubsystem* Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UCalendarSubsystem>())
	{
		Subsystem->OnWeekChangedDelegate.Remove(WeekChangedHandle);
		Subsystem->OnMatchCompletedDelegate.Broadcast(MatchData);
	}
}


void UCalendarLine_Base::OnMatchCreated()
{
	if (UCalendarSubsystem* Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UCalendarSubsystem>())
	{
		Subsystem->AddMatch(MatchData);
	}
}


void UCalendarLine_Base::ChangeLineStatus(int32 CurrentWeek)
{
	if (MatchData.MatchID.Week == CurrentWeek) Button_StartMatch->SetIsEnabled(true);
	else Button_StartMatch->SetIsEnabled(false);
}

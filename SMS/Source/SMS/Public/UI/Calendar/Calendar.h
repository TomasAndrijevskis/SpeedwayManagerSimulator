
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Calendar.generated.h"


class UCalendarWeek;
class UCalendarDataAsset;
class UStandingsWidget;
class UStatisticsWidget;
class UButton;
class ASMS_GameMode;
class UVerticalBox;
class UNumbersBox;
class UNamesBox;

UCLASS()
class SMS_API UCalendar : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;
	
private:
	
	UPROPERTY(meta=(BindWidget))
	UVerticalBox* VB_Content;

	void CreateCalendarWeeks();

	UCalendarWeek* CreateWeek();
	
	UPROPERTY(EditDefaultsOnly)
	UCalendarDataAsset* CalendarDataAsset;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCalendarWeek> CalendarWeekClass;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_OpenStandings;
	
	UPROPERTY(meta = (BindWidget))
	UButton* Button_OpenStatistics;
	
	UFUNCTION()
	void CreateStatisticsWidget();
	
	UFUNCTION()
	void CreateStandingsWidget();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UStatisticsWidget> StatisticsWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UStandingsWidget> StandingsWidgetClass;
};

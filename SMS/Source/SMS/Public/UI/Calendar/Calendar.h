
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Calendar.generated.h"


class UProgram;
class UCalendarRound;
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

	UPROPERTY(meta = (BindWidget))
	UButton* Button_StartGP;
	
	UPROPERTY(meta=(BindWidget))
	UVerticalBox* VB_Content;

	void CreateCalendarRounds();

	UCalendarRound* CreateRound();
	
	UPROPERTY(EditDefaultsOnly)
	UCalendarDataAsset* CalendarDataAsset;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCalendarRound> CalendarRoundClass;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_OpenStandings;
	
	UPROPERTY(meta = (BindWidget))
	UButton* Button_OpenStatistics;
	
	UFUNCTION()
	void CreateStatisticsWidget();
	
	UFUNCTION()
	void CreateStandingsWidget();


	
	UFUNCTION()
	void StartGP();


	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UProgram> ProgramClass;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UStatisticsWidget> StatisticsWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UStandingsWidget> StandingsWidgetClass;
};

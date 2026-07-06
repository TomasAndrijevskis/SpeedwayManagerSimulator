
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Calendar.generated.h"


class ASMS_GameMode;
class UVerticalBox;
class UCalendarLine;
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
	
	UPROPERTY(meta = (BindWidget))
	UNamesBox* NamesBox_HomeText;
	
	UPROPERTY(meta = (BindWidget))
	UNamesBox* NamesBox_VisitorText;

	void CreateMatches();
	
	UCalendarLine* CreateMatch(int HomeTeamID, int VisitorTeamID);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCalendarLine> CalendarLineClass;
	
	int GetRandomTeam();

	void SetTeam(int& Team);
	
	UPROPERTY(EditDefaultsOnly)
	int AmountOfMatches = 3;

	TArray<int> ChosenOptions;
};
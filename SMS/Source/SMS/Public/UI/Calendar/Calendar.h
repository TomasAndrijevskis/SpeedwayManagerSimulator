
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
	
	UCalendarLine* CreateMatch(int32 HomeTeamID, int32 VisitorTeamID);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCalendarLine> CalendarLineClass;
	
	int32 GetRandomTeam();

	void SetTeamID(int32& Team);

	void SetAmountOfMatches();
	
	int32 AmountOfMatches;

	TArray<int32> ChosenOptions;
};
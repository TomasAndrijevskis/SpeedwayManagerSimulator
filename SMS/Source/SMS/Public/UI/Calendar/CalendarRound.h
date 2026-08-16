
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/Calendar/TeamsInMatch.h"
#include "CalendarRound.generated.h"


class UVerticalBox;
class UNumbersBox;
class UCalendarLine;
class UButton;

UCLASS()
class SMS_API UCalendarRound : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetRound(int32 NewRound);

	void CreateMatches(const TArray<FTeamsInMatch>& Matches);
	
private:
	
	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_Round;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VerticalBox_Content;
	
	
	UCalendarLine* CreateMatch(ETeams HomeTeamID, ETeams VisitorTeamID);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCalendarLine> CalendarLineClass;
	
	int32 CurrentRound = 0;
};

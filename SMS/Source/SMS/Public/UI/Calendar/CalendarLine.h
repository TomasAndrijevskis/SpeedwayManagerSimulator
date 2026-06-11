
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CalendarLine.generated.h"


class UNumbersBox;
class UMatchManager;
class ASMS_GameMode;
class ULeagueProgram;
class UButton;
class UNamesBox;

UCLASS()
class SMS_API UCalendarLine : public UUserWidget
{
	GENERATED_BODY()

public:

	void InitializeLine(int NewHomeTeamID, int NewVisitorTeamID);
	
	void SetMatchTeamID(int NewHomeTeamID, int NewVisitorTeamID);
	
	void SetTeamNames(const FText& HomeTeamName, const FText& VisitorTeamName);
	
protected:

	virtual void NativeConstruct() override;
	
private:

	UPROPERTY(meta = (BindWidget))
	UNamesBox* NamesBox_HomeTeamName;

	UPROPERTY(meta = (BindWidget))
	UNamesBox* NamesBox_VisitorTeamName;

	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_HomeTeamScore;

	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_VisitorTeamScore;
	
	UPROPERTY(meta = (BindWidget))
	UButton* Button_StartMatch;

	UFUNCTION()
	void StartMatch();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ULeagueProgram> LeagueProgramClass;

	UPROPERTY()
	UMatchManager* MatchManager;
	
	int HomeTeamID;
	
	int VisitorTeamID;
};

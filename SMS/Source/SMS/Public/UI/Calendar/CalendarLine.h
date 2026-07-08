
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CalendarLine.generated.h"


class UScoreManager;
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
	
	void DisplayTeamNames(const FText& HomeTeamName, const FText& VisitorTeamName);
	
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

	void OnMatchEnded();
	
	UFUNCTION()
	void StartMatch();

	void DisplayFinalScore(int HomePoints, int VisitorPoints);

	UFUNCTION()
	void InitializeManagers();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ULeagueProgram> LeagueProgramClass;

	UPROPERTY()
	UMatchManager* MatchManager;

	UPROPERTY()
	UScoreManager* ScoreManager;
	
	int HomeTeamID;
	
	int VisitorTeamID;
};


#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CalendarLine.generated.h"


class UScoreManager;
class ULeagueProgram;
class UMatchManager;
class UNumbersBox;
class UButton;
class UNamesBox;

UCLASS()
class SMS_API UCalendarLine : public UUserWidget
{
	GENERATED_BODY()

public:

	void InitializeLine(int32 NewHomeTeamID, int32 NewVisitorTeamID);
	
	void SetMatchTeamID(int32 NewHomeTeamID, int32 NewVisitorTeamID);
	
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

	void DisplayFinalScore(int32 HomePoints, int32 VisitorPoints);

	UFUNCTION()
	void InitializeManagers();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ULeagueProgram> LeagueProgramClass;

	UPROPERTY()
	TObjectPtr<UMatchManager> MatchManager;

	UPROPERTY()
	TObjectPtr<UScoreManager> ScoreManager;
	
	int32 HomeTeamID;
	
	int32 VisitorTeamID;
};

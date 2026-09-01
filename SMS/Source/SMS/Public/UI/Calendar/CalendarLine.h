
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/TeamData/ETeams.h"
#include "CalendarLine.generated.h"


class UProgram;
class UScoreManager;
class UMatchManager;
class UNumbersBox;
class UButton;
class UNamesBox;

UCLASS()
class SMS_API UCalendarLine : public UUserWidget
{
	GENERATED_BODY()

public:

	void InitializeLine(int32 HomeTeamID, int32 VisitorTeamID);
	
	void SetMatchTeams(ETeams NewHomeTeam, ETeams NewVisitorTeam);
	
	void DisplayTeamNames(const FString& HomeTeamName, const FString& VisitorTeamName);
	
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
	TSubclassOf<UProgram> ProgramClass;

	UPROPERTY()
	TObjectPtr<UMatchManager> MatchManager;

	UPROPERTY()
	TObjectPtr<UScoreManager> ScoreManager;
	
	ETeams HomeTeam;
	
	ETeams VisitorTeam;
};

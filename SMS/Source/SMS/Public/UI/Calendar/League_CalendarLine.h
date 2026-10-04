
#pragma once

#include "CoreMinimal.h"
#include "Data/TeamData/ETeams.h"
#include "UI/BaseClasses/CalendarLine_Base.h"
#include "League_CalendarLine.generated.h"


UCLASS()
class SMS_API ULeague_CalendarLine : public UCalendarLine_Base
{
	GENERATED_BODY()

public:

	void InitializeLine(int32 HomeTeamID, int32 VisitorTeamID);
	
	void SetMatchTeams(ETeams NewHomeTeam, ETeams NewVisitorTeam);
	
	void DisplayTeamNames(const FString& HomeTeamName, const FString& VisitorTeamName);

protected:

	UPROPERTY(meta = (BindWidget))
	UNamesBox* NamesBox_HomeTeamName;

	UPROPERTY(meta = (BindWidget))
	UNamesBox* NamesBox_VisitorTeamName;

	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_HomeTeamScore;

	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_VisitorTeamScore;

private:

	virtual void CollectMatchScore() override;

	virtual void OnMatchEnded() override;

	virtual void StartMatch() override;

	void DisplayFinalScore(int32 HomePoints, int32 VisitorPoints);

	ETeams HomeTeam;
	
	ETeams VisitorTeam;

	int32 HomeTeamScore = 0;
	
	int32 VisitorTeamScore = 0;
};

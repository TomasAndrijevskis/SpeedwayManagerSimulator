
#pragma once

#include "CoreMinimal.h"
#include "Data/TeamData/TeamRosterData.h"
#include "MatchManager.generated.h"

class ASMS_GameMode;
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMatchFinished, int, int);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnScoreUpdated, int, int);
UCLASS()
class SMS_API UMatchManager : public UObject
{
	GENERATED_BODY()

public:

	void Init(ASMS_GameMode* CurrentGameMode);
	
	void SetTeamsID(int NewHomeTeamID, int NewVisitorTeamID);

	void UpdateScore(int NewHomeTeamScore, int NewVisitorTeamScore);

	int GetHomeTeamScore() const;
	
	int GetVisitorTeamScore() const;
	
	FTeamRosterData* GetHomeTeamData() const;

	FTeamRosterData* GetVisitorTeamData() const;

	FOnMatchFinished OnMatchFinishedDelegate;

	FOnScoreUpdated OnScoreUpdatedDelegate;

private:

	UPROPERTY()
	ASMS_GameMode* GameMode;
	
	UPROPERTY()
	int HomeTeamID;

	UPROPERTY()
	int VisitorTeamID;

	int HomeTeamScore = 0;

	int VisitorTeamScore = 0;
};

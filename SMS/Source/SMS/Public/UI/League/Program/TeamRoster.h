
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/TeamData/TeamMatchData.h"
#include "Managers/ScoreManager.h"
#include "TeamRoster.generated.h"


class UMatchManager;
class UTeamManager;
class UVerticalBox;
class UNumbersBox;
class UNamesBox;
class URacerStatsLine;

UCLASS()
class SMS_API UTeamRoster : public UUserWidget
{
	GENERATED_BODY()

public:
	
	void InitializeTeam(FTeamMatchData* NewTeamData, const UMatchManager* MatchManagerRef);

	UTeamManager* GetTeamManager() const;
	
private:
	
	UPROPERTY(meta = (BindWidget))
	UNamesBox* NamesBox_TeamName;

	UPROPERTY(meta = (BindWidget))
	UNamesBox* NamesBox_TeamStatus;

	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_TeamPoints;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VB_Content;
	
	void CreateRacerStatLines(const UScoreManager* ScoreManagerRef);
	
	URacerStatsLine* CreateRacerStatLine(int32 ID);

	void UpdateTeamPoints(int32 TeamId, int32 NewPoints);

	void DisplayTeamName();

	void InitializeManagers(FTeamMatchData* NewTeamData, const UMatchManager* MatchManagerRef);

	void DisplayTeamStatus();

	void BindDelegates();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<URacerStatsLine> RacerStatsLineClass;

	UPROPERTY()
	TObjectPtr<UScoreManager> ScoreManager;

	UPROPERTY()
	TObjectPtr<UTeamManager> TeamManager;
	
	int32 RacersAmount = 6;

	int32 TeamID = 0;
};

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
class ULeague_RacerStatsLine;

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
	
	ULeague_RacerStatsLine* CreateRacerStatLine(int32 ID);

	void UpdateTeamPoints(ETeams TeamToUpdate, int32 NewPoints);

	void DisplayTeamName();

	void InitializeManagers(FTeamMatchData* NewTeamData, const UMatchManager* MatchManagerRef);

	void DisplayTeamStatus();

	void BindDelegates();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ULeague_RacerStatsLine> RacerStatsLineClass;

	UPROPERTY()
	TObjectPtr<UScoreManager> ScoreManager;

	UPROPERTY()
	TObjectPtr<UTeamManager> TeamManager;
	
	int32 RacersAmount = 6;

	ETeams Team = ETeams::Nothing;
};
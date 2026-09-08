
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
	
	void InitializeTeam(bool IsVisitor);

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
	
	void CreateRacerStatLines();
	
	ULeague_RacerStatsLine* CreateRacerStatLine(int32 ID);

	void UpdateTeamPoints(int32 NewPoints);

	void DisplayTeamName();

	void InitializeManagers(bool IsVisitor);

	void DisplayTeamStatus();

	void BindDelegates();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ULeague_RacerStatsLine> RacerStatsLineClass;

	UPROPERTY()
	TObjectPtr<UTeamManager> TeamManager;
	
	int32 RacersAmount = 6;
};
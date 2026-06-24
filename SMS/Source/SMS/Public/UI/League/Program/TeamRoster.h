
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Managers/TeamManager.h"
#include "TeamRoster.generated.h"


class UScoreManager;
class UTeamsDataAsset;
class UVerticalBox;
class UNumbersBox;
class UNamesBox;
class URacerStatsLine;

UCLASS()
class SMS_API UTeamRoster : public UUserWidget
{
	GENERATED_BODY()

public:
	
	void InitializeTeam(int NewTeamID, bool bStatus);

	UTeamManager* GetTeamManager() const;
	
protected:

	virtual void NativeConstruct() override;
	
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
	
	URacerStatsLine* CreateRacerStatLine(int ID);

	void UpdateTeamPoints(int NewPoints);

	void SetTeamName();

	void InitializeManagers();

	void SetTeamStatus();

	void BindDelegates();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<URacerStatsLine> RacerStatsLineClass;

	UPROPERTY()
	UScoreManager* ScoreManager;

	UPROPERTY()
	UTeamManager* TeamManager;
	
	bool IsVisitorTeam = false;
	
	int RacersAmount = 6;

	int TeamID;
};

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/TeamData/TeamRosterData.h"
#include "Managers/TeamRostersManager.h"
#include "TeamRoster.generated.h"


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

	TArray<URacerStatsLine*>& GetRacers();

	void SetTeamStatus(bool isVisitorTeam);

	void SetTeamData(const FTeamRosterData& NewTeamData);

	UPROPERTY()
	UTeamRostersManager* TeamRosterManager;
	
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

	void FillTeamRosters();

	void SetTeamName();

	void InitializeManagers();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<URacerStatsLine> RacerStatsLineClass;
	
	UPROPERTY()
	TArray<URacerStatsLine*> RacersLines;

	UPROPERTY(VisibleAnywhere)
	bool IsVisitorTeam = false;

	UPROPERTY(VisibleAnywhere)
	int RacersAmount = 6;

	UPROPERTY()
	FTeamRosterData TeamData;
};
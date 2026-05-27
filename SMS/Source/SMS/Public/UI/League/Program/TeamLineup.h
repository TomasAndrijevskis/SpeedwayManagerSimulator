
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/RacersData/RacerStats.h"
#include "TeamLineup.generated.h"


class UTeamsDataAsset;
class UVerticalBox;
class UNumbersBox;
class UNamesBox;
class URacerStatsLine;

UCLASS()
class SMS_API UTeamLineup : public UUserWidget
{
	GENERATED_BODY()

public:

	TArray<URacerStatsLine*>& GetRacers();

	void SetIsVisitorTeam(bool isVisitorTeam);

	void SetTeamName(const FString& NewTeamName);
	
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

	void FillTeamLineups();

	void FillTeamData(URacerStatsLine* const& Racer, TArray<FRacerStats> TeamData);
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<URacerStatsLine> RacerStatsLineClass;
	
	UPROPERTY()
	TArray<URacerStatsLine*> Racers;

	UPROPERTY(VisibleAnywhere)
	bool IsVisitorTeam = false;

	UPROPERTY(VisibleAnywhere)
	int RacersAmount = 6;

	UPROPERTY()
	FString TeamName;
};
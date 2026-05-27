
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

	void SetTeam();

	void FillTeam(URacerStatsLine* const& Racer ,  TArray<FRacerStats> TeamData);
	
	UPROPERTY(EditAnywhere)
	bool IsVisitorTeam = false;

	UPROPERTY(VisibleAnywhere)
	int RacersAmount = 6;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<URacerStatsLine> RacerStatsLineClass;

	UPROPERTY(EditDefaultsOnly)
	UTeamsDataAsset* TeamLineupsDataAsset;
	
	UPROPERTY()
	TArray<URacerStatsLine*> Racers;
};
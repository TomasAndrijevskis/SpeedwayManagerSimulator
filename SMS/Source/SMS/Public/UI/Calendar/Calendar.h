
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/TeamData/TeamRosterData.h"
#include "Calendar.generated.h"


class UMatchManager;
class ULeagueProgram;
class ASMS_GameMode;
class UButton;
class UNamesBox;

UCLASS()
class SMS_API UCalendar : public UUserWidget
{
	GENERATED_BODY()

public:

protected:

	virtual void NativeConstruct() override;
	
private:

	UPROPERTY(meta = (BindWidget))
	UNamesBox* NamesBox_HomeText;
	
	UPROPERTY(meta = (BindWidget))
	UNamesBox* NamesBox_VisitorText;

	UPROPERTY(meta = (BindWidget))
	UNamesBox* NamesBox_HomeTeamName;

	UPROPERTY(meta = (BindWidget))
	UNamesBox* NamesBox_VisitorTeamName;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_StartMatch;

	void CreateMatch();

	UFUNCTION()
	void StartMatch();

	void GetRandomTeams();
	
	UPROPERTY()
	ASMS_GameMode* GameMode;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ULeagueProgram> LeagueProgramClass;

	UPROPERTY()
	UMatchManager* MatchManager;

	FTeamRosterData* HomeTeamData;

	FTeamRosterData* VisitorTeamData;
};
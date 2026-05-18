
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LeagueProgramm.generated.h"

class UBackgroundBlur;
class UVerticalBox;
class UTeamLineup;
class UButton;
class URace;

UCLASS()
class SMS_API ULeagueProgramm : public UUserWidget
{
	GENERATED_BODY()
	
public:

protected:

	virtual void NativeConstruct() override;
	
private:

	UPROPERTY(meta = (BindWidget))
	URace* Race_One;

	UPROPERTY(meta = (BindWidget))
	URace* Race_Two;

	UPROPERTY(meta = (BindWidget))
	URace* Race_Three;

	UPROPERTY(meta = (BindWidget))
	URace* Race_Four;

	UPROPERTY(meta = (BindWidget))
	URace* Race_Five;

	UPROPERTY(meta = (BindWidget))
	URace* Race_Six;

	UPROPERTY(meta = (BindWidget))
	URace* Race_Seven;

	UPROPERTY(meta = (BindWidget))
	URace* Race_Eight;

	UPROPERTY(meta = (BindWidget))
	URace* Race_Nine;

	UPROPERTY(meta = (BindWidget))
	URace* Race_Ten;

	UPROPERTY(meta = (BindWidget))
	URace* Race_Eleven;

	UPROPERTY(meta = (BindWidget))
	URace* Race_Twelve;

	UPROPERTY(meta = (BindWidget))
	URace* Race_Thirteen;

	UPROPERTY(meta = (BindWidget))
	URace* Race_Fourteen;

	UPROPERTY(meta = (BindWidget))
	URace* Race_Fifteen;
	
	UPROPERTY(meta = (BindWidget))
	UTeamLineup* TeamLineup_HomeTeam;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_SimulateRace;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_ShowTeams;
	
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VB_Teams;

	UPROPERTY(meta = (BindWidget))
	UBackgroundBlur* BackgroundBlur;
	
	UFUNCTION()
	void SimulateRace();

	void FillRacers(FString Name, int Id);

	void SetRaceID();
	
	void CreateRacesArray();

	void BindDelegates();

	UFUNCTION()
	void ShowTeams();
	
	TArray<URace*> Races;
};
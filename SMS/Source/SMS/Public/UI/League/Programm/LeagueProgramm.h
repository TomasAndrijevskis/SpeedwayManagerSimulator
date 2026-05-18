
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LeagueProgramm.generated.h"

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
	UTeamLineup* TeamLineup_HomeTeam;
	
	UPROPERTY(meta = (BindWidget))
	URace* Race_First;

	UPROPERTY(meta = (BindWidget))
	URace* Race_Second;

	UPROPERTY(meta = (BindWidget))
	URace* Race_Third;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_SimulateRace;
	
	UFUNCTION()
	void SimulateRace();

	void FillRacers(FString Name, int Id);
	
	TArray<URace*> Races;
};
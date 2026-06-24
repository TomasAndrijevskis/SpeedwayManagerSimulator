
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FillNominatedRaces.generated.h"


class UMatchManager;
class UTeamRoster;
class UNominatedRace;
class UVerticalBox;
class UButton;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnConfirmed, const bool)
UCLASS()
class SMS_API UFillNominatedRaces : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void InitializeWidget();

	void InitializeManagers();
	
	FOnConfirmed OnConfirmedDelegate;
	
private:

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Confirm;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VB_Content;

	void CreateNominatedRaces();

	UNominatedRace* CreateNominatedRace();
	
	void BindDelegates();

	UFUNCTION()
	void RemoveWidget();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UNominatedRace> NominatedRaceClass;

	UPROPERTY()
	TArray<UNominatedRace*> NominatedRaces;

	UPROPERTY()
	UMatchManager* MatchManager;
};


#pragma once

#include "CoreMinimal.h"
#include "UI/BaseClasses/RaceLine_Base.h"
#include "League_RaceLine_Base.generated.h"


class USlider;
class UChooseBox;
class UOverlay;
class URacerMatchManager;

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnRacerReplaced, ULeague_RaceLine_Base*, const FString&, URacerMatchManager*);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRacerChosen, ULeague_RaceLine_Base*, const FString&);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSelectedRacerChanged, ULeague_RaceLine_Base*, URacerMatchManager*, bool);
UCLASS()
class SMS_API ULeague_RaceLine_Base : public URaceLine_Base
{
	GENERATED_BODY()

public:

	void ChangeChooseBoxStatus(bool Status);
	
	void SetRacerData(URacerMatchManager* RacerManagerRef, bool IsReplacement);
	
	void CrossOutRacer();
	
	void AddReplacementOption(FString SelectedItem);
	virtual void AddMainOption(FString SelectedItem){};
	void RemoveFromReplacementSelection(FString SelectedItem);
	virtual void RemoveFromMainSelection(FString SelectedItem){};

	URacerMatchManager* GetOriginalRacerManager() const;

	bool IsVisitor() const;
	
	FOnRacerReplaced OnRacerReplacedDelegate;

	FOnRacerChosen OnRacerChosenDelegate;
	
	FOnSelectedRacerChanged OnSelectedRacerChangedDelegate;
	
protected:
	
	UPROPERTY(meta = (BindWidget))
	UOverlay* Overlay_RacerName;
	
	UPROPERTY(meta = (BindWidget))
	UChooseBox* ChooseBox_RacerReplacement;

	virtual void InitializeWidget() override;
	
	virtual void BindDelegates() override;

	UFUNCTION()
	virtual void OnRacerChosen(FString SelectedItem, ESelectInfo::Type SelectionType){};

	UFUNCTION()
	virtual void OnRacerReplaced(FString SelectedItem, ESelectInfo::Type SelectionType);

	
private:

	USlider* CreateSlider();
	
	UPROPERTY()
	URacerMatchManager* OriginalRacerManager;
};

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseClasses/RacerStatsLine_Base.h"
#include "League_RacerStatsLine.generated.h"


class URacerMatchManager;
class UChooseBox;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRacerSelected, const FString&, int32);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnSelectedOptionChanged, const ULeague_RacerStatsLine*, const FString&, const TObjectPtr<URacerMatchManager>&);
UCLASS()
class SMS_API ULeague_RacerStatsLine : public URacerStatsLine_Base
{
	GENERATED_BODY()

public:

	void AddOption(const TObjectPtr<URacerMatchManager>& NewRacerManager);

	void RemoveOption(const FString& Option);

	void ChooseRandomOption(); // for testing

	void LockRacer();

	int GetNumberOfOptions() const;
	
	FOnRacerSelected OnRacerSelectedDelegate;

	FOnSelectedOptionChanged OnSelectedOptionChangedDelegate;
	
protected:

	virtual void NativeConstruct() override;
	
private:
	
	UPROPERTY(meta = (BindWidget))
	UChooseBox* ChooseBox_Racer;

	void OnRacerChosen(FString SelectedOption, ESelectInfo::Type SelectionType);
	
	TArray<TObjectPtr<URacerMatchManager>> Racers;

	TObjectPtr<URacerMatchManager> SelectedData;

	FString PreviousOption = "";
};
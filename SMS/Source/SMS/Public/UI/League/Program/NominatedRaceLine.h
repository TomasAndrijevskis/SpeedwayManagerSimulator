
#pragma once

#include "CoreMinimal.h"
#include "RaceLineBase.h"
#include "Data/RaceData/RaceLineData.h"
#include "NominatedRaceLine.generated.h"


class UTeamManager;
class UChooseBox;
class UNumbersBox;

UCLASS()
class SMS_API UNominatedRaceLine : public URaceLineBase
{
	GENERATED_BODY()
	
public:

	virtual void SetRaceLineData(const FRaceLineData& NewRaceLineData) override;


protected:

	virtual void NativeConstruct() override;
	
	//virtual void SetRacerName(const FString& NewRacerName) override;
	
private:

	UPROPERTY(meta = (BindWidget))
	UChooseBox* ChooseBox_ChooseRacer;

	void InitializeWidget();

	void SetTeamManager(TArray<UTeamManager*> TeamManagersRef);

	UFUNCTION()
	void OnRacerChosen(FString SelectedItem, ESelectInfo::Type SelectionType);

	void FillOptions();
	
	void AddOption(const FRacerMatchData& Data, URacerManager* NewRacerManager);
	
	UPROPERTY()
	UTeamManager* TeamManager;
	
	UPROPERTY()
	TMap<URacerManager*, FRacerMatchData> RacerManagers;
};
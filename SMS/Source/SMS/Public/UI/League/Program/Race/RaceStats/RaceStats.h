
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/RaceData/RaceResultData.h"
#include "RaceStats.generated.h"


class URaceStatsManager;
class UHorizontalBox;
class URaceLineStat;

UCLASS()
class SMS_API URaceStats : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void InitializeWidget();

	void UpdateStats(const TArray<FRaceResultData>& RaceResultData) const;
	
private:

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HorizontalBox_Content;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<URaceLineStat> RaceLineStatClass;

	void CreateRaceLineStats();

	URaceLineStat* CreateRaceLineStat(int32 ID);

	void InitializeManager();
	
	UPROPERTY()
	TObjectPtr<URaceStatsManager> RaceStatsManager;

	int32 RaceLineStatsAmount = 4;
	
};

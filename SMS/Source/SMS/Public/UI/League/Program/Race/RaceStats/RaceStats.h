
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RaceStats.generated.h"


class UHorizontalBox;
class URaceLineStat;

UCLASS()
class SMS_API URaceStats : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void InitializeWidget();

protected:

	virtual void NativeConstruct() override;
	
private:

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HorizontalBox_Content;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<URaceLineStat> RaceLineStatClass;

	void CreateRaceLineStats();

	URaceLineStat* CreateRaceLineStat(int32 ID);
	
	int32 RaceLineStatsAmount = 4;
	
};

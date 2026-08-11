
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/RacersData/RacerStatistics.h"
#include "StatisticsWidget.generated.h"


class UScrollBox;
class UWrapBox;
class UButton;
class UVerticalBox;
class UStatisticsLine;

UCLASS()
class SMS_API UStatisticsWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void InitializeStatisticsWidget();

	UStatisticsLine* CreateNewStatisticsLine(const FRacerStatistics& Data);

protected:

	virtual void NativeConstruct() override;
	
private:
	
	UPROPERTY(meta=(BindWidget))
	UWrapBox* WrapBox_StatisticsBox;

	UPROPERTY(meta=(BindWidget))
	UButton* Button_Exit;

	UFUNCTION()
	void RemoveWidget();

	void SortLines();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UStatisticsLine> StatisticsLineClass;

	TArray<TObjectPtr<UStatisticsLine>> StatisticsLines;
	
};

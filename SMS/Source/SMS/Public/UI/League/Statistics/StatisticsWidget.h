
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatisticsWidget.generated.h"


class UButton;
class UVerticalBox;
class UStatisticsLine;

UCLASS()
class SMS_API UStatisticsWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void InitializeStatisticsWidget();

	void CreateNewStatisticsLine(int32 ID);
	
	void UpdateExistingStatisticsLine();

protected:

	virtual void NativeConstruct() override;
	
private:

	UPROPERTY(meta=(BindWidget))
	UVerticalBox* VerticalBox_StatisticsBox;

	UPROPERTY(meta=(BindWidget))
	UButton* Button_Exit;

	UFUNCTION()
	void RemoveWidget();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UStatisticsLine> StatisticsLineClass;

	UPROPERTY()
	TArray<UStatisticsLine*> ExistingStatisticsLines;
	
};

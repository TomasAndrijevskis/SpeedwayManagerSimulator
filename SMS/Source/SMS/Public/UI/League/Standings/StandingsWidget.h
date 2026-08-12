
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/TeamData/TeamStatistics.h"
#include "StandingsWidget.generated.h"

class UVerticalBox;
class UButton;
class UStandingsLine;

UCLASS()
class SMS_API UStandingsWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void InitializeStandingsWidget();
	
private:

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Exit;

	UPROPERTY(meta=(BindWidget))
	UVerticalBox* VerticalBox_Standings;

	UStandingsLine* CreateNewStandingsLine(const FTeamStatistics& TeamStats);

	UFUNCTION()
	void RemoveWidget();

	void SortLines();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UStandingsLine> StandingsLineClass;

	TArray<TObjectPtr<UStandingsLine>> StandingsLines;
};

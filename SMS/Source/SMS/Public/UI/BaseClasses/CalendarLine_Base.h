
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/Calendar/MatchData.h"
#include "CalendarLine_Base.generated.h"


class UProgram;
class UMatchManager;
class UNumbersBox;
class UButton;
class UNamesBox;

UCLASS()
class SMS_API UCalendarLine_Base : public UUserWidget
{
	GENERATED_BODY()

public:

	void BindDelegates();
	
	void SetMatchData(const FMatchData& NewMatchData)
	{
		UE_LOG(LogTemp, Error, TEXT("=================="));
		UE_LOG(LogTemp, Warning, TEXT("Season %i"), NewMatchData.MatchID.Season);
		UE_LOG(LogTemp, Warning, TEXT("Week %i"), NewMatchData.MatchID.Week);
		UE_LOG(LogTemp, Warning, TEXT("Match %i"), NewMatchData.MatchID.WeekMatchNumber);
		UE_LOG(LogTemp, Error, TEXT("=================="));
		MatchData = NewMatchData;
	}
	
	FMatchData& GetMatchData() {return MatchData;}
	
protected:

	UPROPERTY(meta = (BindWidget))
	UButton* Button_StartMatch;
	
	virtual void NativeConstruct() override;

	virtual void CollectMatchScore() {};

	virtual void OnMatchEnded();

	UFUNCTION()
	virtual void StartMatch() {};

	void OnMatchCreated();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UProgram> ProgramClass;
	
private:

	void ChangeLineStatus(int32 CurrentWeek);

	UPROPERTY()
	FMatchData MatchData;

	FDelegateHandle WeekChangedHandle;
};

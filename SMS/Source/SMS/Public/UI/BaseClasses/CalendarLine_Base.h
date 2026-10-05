
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
	
	void SetMatchID(int32 NewMatchID) {MatchID = NewMatchID;}

	int32 GetMatchID() const {return MatchID;}
	
protected:

	UPROPERTY(meta = (BindWidget))
	UButton* Button_StartMatch;
	
	virtual void NativeConstruct() override;

	virtual void CollectMatchScore() {};

	virtual void OnMatchEnded();

	UFUNCTION()
	virtual void StartMatch() {};

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UProgram> ProgramClass;
	
private:
	
	int32 MatchID = 0;
};

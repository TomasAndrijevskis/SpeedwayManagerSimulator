
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Race.generated.h"

class UScoreCounter;
class UTextBlock;
class URaceLine;

UCLASS()
class SMS_API URace : public UUserWidget
{
	GENERATED_BODY()

public:

protected:

	virtual void NativeConstruct() override;
	
private:

	UPROPERTY(meta = (BindWidget))
	URaceLine* RaceLine_First;

	UPROPERTY(meta = (BindWidget))
	URaceLine* RaceLine_Second;
	
	UPROPERTY(meta = (BindWidget))
	URaceLine* RaceLine_Third;
	
	UPROPERTY(meta = (BindWidget))
	URaceLine* RaceLine_Fourth;

	UPROPERTY(meta = (BindWidget))
	UScoreCounter* ScoreCounter;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_RaceNumber;
};

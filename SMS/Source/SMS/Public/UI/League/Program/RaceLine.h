
#pragma once

#include "CoreMinimal.h"
#include "RaceLineBase.h"
#include "RaceLine.generated.h"


class UNamesBox;

UCLASS()
class SMS_API URaceLine : public URaceLineBase
{
	GENERATED_BODY()

protected:

	virtual void SetRacerName(const FString& NewRacerName) override;
	
private:
	
	UPROPERTY(meta = (BindWidget))
	UNamesBox* NamesBox_RacerName;
};

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseClasses/RacerStatsLine_Base.h"
#include "GP_RacerStatsLine.generated.h"

class UHorizontalBox;
class UNumbersBox;
class UNamesBox;

UCLASS()
class SMS_API UGP_RacerStatsLine : public URacerStatsLine_Base
{
	GENERATED_BODY()

public:

	void SetRacerName(const FString& Name);

	void UpdateRacerPosition(int32 NewPosition);
	
private:
	
	UPROPERTY(meta = (BindWidget))
	UNamesBox* NamesBox_RacerName;

	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_RacerPosition;
};

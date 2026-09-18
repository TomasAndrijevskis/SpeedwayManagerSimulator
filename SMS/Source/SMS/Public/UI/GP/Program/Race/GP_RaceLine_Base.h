
#pragma once

#include "CoreMinimal.h"
#include "UI/BaseClasses/RaceLine_Base.h"
#include "GP_RaceLine_Base.generated.h"


class UNamesBox;
class UNumbersBox;

UCLASS()
class SMS_API UGP_RaceLine_Base : public URaceLine_Base
{
	GENERATED_BODY()

public:

	virtual void SetRacerData(URacerMatchManager* RacerManagerRef, bool IsReplacement) override;
	
protected:

	virtual void SetRacerName(const FString& NewRacerName) override;
	
private:
	

	UPROPERTY(meta = (BindWidget))
	UNamesBox* NamesBox_RacerName;
	
};


#pragma once

#include "CoreMinimal.h"
#include "Data/RacersData/RacerData.h"
#include "RacerManager.generated.h"


UCLASS()
class SMS_API URacerManager : public UObject
{
	GENERATED_BODY()

public:

	void Init(int RacerNumber, const FRacerData& RacerData);

private:

	int Number;
	
	FRacerData Data;
};

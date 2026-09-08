
#pragma once

#include "CoreMinimal.h"
#include "Data/RacersData/RacerMatchData.h"
#include "RacerCareerManager.generated.h"

UCLASS()
class SMS_API URacerCareerManager : public UObject
{
	GENERATED_BODY()


public:

	void Initialize(const FRacerData& RacerData);

	FRacerData& GetRacerData();
	
private:

	FRacerData Data;
};

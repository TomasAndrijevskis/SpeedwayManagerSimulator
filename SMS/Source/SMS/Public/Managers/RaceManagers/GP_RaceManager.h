
#pragma once

#include "CoreMinimal.h"
#include "Managers/RaceManagers/RaceManager_Base.h"
#include "GP_RaceManager.generated.h"


UCLASS()
class SMS_API UGP_RaceManager : public URaceManager_Base
{
	GENERATED_BODY()
	

public:

	
private:

	virtual void SimulateRace() override;
};


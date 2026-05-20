
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SMS_GameMode.generated.h"


UCLASS()
class SMS_API ASMS_GameMode : public AGameMode
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	
};

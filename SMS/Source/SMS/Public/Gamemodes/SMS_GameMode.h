
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SMS_GameMode.generated.h"


class UPointsManager;

UCLASS()
class SMS_API ASMS_GameMode : public AGameMode
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	UPointsManager* GetPointsManager() const;
	
private:
	
	UPROPERTY()
	UPointsManager* PointsManager;
	
};


#pragma once

#include "CoreMinimal.h"
#include "TeamData.h"
#include "Engine/DataAsset.h"
#include "TeamsDataAsset.generated.h"

UCLASS()
class SMS_API UTeamsDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly)
	TArray<FTeamData> Teams;
};


#pragma once

#include "CoreMinimal.h"
#include "TeamRostersManager.generated.h"


UCLASS()
class SMS_API UTeamRostersManager : public UObject
{
	GENERATED_BODY()

public:

	void AddRacer(FString Name, int Id);

	void ForEachRacer(TFunction<void(const FString&, int)> Callback);
	
private:
	
	TMap<int, FString> Racers;
};

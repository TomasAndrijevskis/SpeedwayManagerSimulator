
#pragma once

#include "CoreMinimal.h"
#include "Data/Calendar/MatchData.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CalendarSubsystem.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMatchCompleted, const FMatchData&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnWeekChanged, int32);
UCLASS()
class SMS_API UCalendarSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	void BindDelegate();
	
	int32 GetCurrentWeek() const {return CurrentWeek;}

	int32 GetCurrentSeason() const {return CurrentSeason;}

	void AddMatch(const FMatchData& Match);
	
	FOnMatchCompleted OnMatchCompletedDelegate;

	FOnWeekChanged OnWeekChangedDelegate;
	
private:

	void UpdateMatchStatus(const FMatchData& MatchData);

	void CheckWeekMatches();

	UPROPERTY()
	TArray<FMatchData> Matches;
	
	int32 CurrentWeek = 1;

	int32 CurrentSeason = 33;
};

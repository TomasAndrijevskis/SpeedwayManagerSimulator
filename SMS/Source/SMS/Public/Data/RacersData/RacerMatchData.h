#pragma once

#include "CoreMinimal.h"
#include "RacerData.h"
#include "RacerMatchData.generated.h"


USTRUCT(BlueprintType)
struct FRacerMatchData
{
	GENERATED_BODY()

	UPROPERTY()
	FRacerData RacerData;

	//number during match 1-6 / 7-12
	UPROPERTY()
	int32 RacerNumber;

	bool IsVisitor() const
	{
		return RacerNumber >= 7;
	}

	bool IsOnJuniorPosition() const
	{
		return RacerNumber == 5 || RacerNumber == 11;
	}

	int32 GetRacerID() const
	{
		return RacerData.ID;
	}
	
	int32 GetBaseRating() const
	{
		return RacerData.RacerStats.Rating;
	}

	int32 GetReaction() const
	{
		return RacerData.RacerStats.Reaction;
	}

	int32 GetDrivingSkill(ETrackTypes TrackType) const
	{
		return RacerData.RacerStats.DrivingSkillsOnEachTrack[TrackType];
	}

	int32 GetAdaptability() const
	{
		return RacerData.RacerStats.Adaptability;
	}

	int32 GetRacerNumber() const
	{
		return RacerNumber;
	}
	
	int32 GetRacerAge() const
	{
		return RacerData.Age;
	}
	
	FString& GetRacerName()
	{
		return RacerData.Name;
	}

	FString GetRacerTeamName() const
	{
		return StaticEnum<ETeams>()->GetDisplayNameTextByValue(static_cast<int32>(RacerData.InitialTeam)).ToString();
	}
};

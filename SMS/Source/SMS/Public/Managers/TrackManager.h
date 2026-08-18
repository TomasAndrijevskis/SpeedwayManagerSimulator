
#pragma once

#include "CoreMinimal.h"
#include "Data/Track/TrackData.h"
#include "TrackManager.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FOnTrackUpdateRequest, int32);

UCLASS()
class SMS_API UTrackManager : public UObject
{
	GENERATED_BODY()

public:

	void InitializeManager(const FTrackData& NewTrackData);

	void UpdateTrackType();
	
	void SetHomeTeamTrackData(const FTrackData& NewTrackData);

	float GetGateModifier(int32 GateID);

	float GetDrivingModifier();
	
	ETrackTypes GetCurrentTrackType() const;

	FOnTrackUpdateRequest OnTrackUpdateRequestDelegate;
	
private:

	void SetInitialTrackType();

	void TryUpdateTrack(int32 CurrentRace);
	
	ETrackTypes GetNewTrackType(const float Total);
	
	FTrackData TrackData;

	ETrackTypes CurrentTrackType;

	ETrackTypes DeniedOption;
};


#pragma once

#include "CoreMinimal.h"
#include "CompetitionRules.h"
#include "Data/RaceData/FinalQualifier.h"
#include "GP_Rules.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnScoreUpdatedGP, int32);
UCLASS()
class SMS_API UGP_Rules : public UCompetitionRules
{
	GENERATED_BODY()

public:

	virtual void SetupMatch() override;

	virtual void PopulateRacers() override;

	virtual bool CanStartMatch() const override;

	virtual void MakeRandomRosters() override;

	void SortRacers();

	void AddQualifiedRacers(const FFinalQualifier& QualifiedData) {FinalQualifiedRacers.Add(QualifiedData);}
	
	TArray<TObjectPtr<URacerMatchManager>>& GetRacers() { return Racers; }	

	FOnScoreUpdatedGP OnScoreUpdatedDelegate;
	
private:
	
	virtual void CollectRacerStatistics() override;

	virtual void PrepareToEndMatch() override;

	virtual void HandleMatchClosed() override;

	virtual void HandleRaceFinished() override;
	
	virtual void InitializeRules() override;
	
	void RequestToAssignRacersToCertainRace(URacerMatchManager* RacerManager, int32 RaceID);
	
	void HandleLineup();

	void HandleTrack();

	void SetNominatedRaceLines(const TArray<int32>& RacersNumbers);

	void FillNominatedRaceLines(const TArray<int32>& RacersNumbers);

	void SetFinalRace();

	void FillFinalRace();
	
	UPROPERTY()
	TArray<TObjectPtr<URacerMatchManager>> Racers;
	
	UPROPERTY()
	TArray<FFinalQualifier> FinalQualifiedRacers;
	
	TArray<int32> Semifinal1Racers = {0, 3, 4, 7};
	
	TArray<int32> Semifinal2Racers = {1, 2, 5, 6};
};

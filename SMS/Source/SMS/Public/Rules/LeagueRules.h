
#pragma once

#include "CoreMinimal.h"
#include "CompetitionRules.h"
#include "Data/TeamData/ETeams.h"
#include "Data/TeamData/TeamMatchData.h"
#include "LeagueRules.generated.h"


class UScoreManager;
class UTeamManager;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnRacerManagersCreated, TArray<UTeamManager*>);
UCLASS()
class SMS_API ULeagueRules : public UCompetitionRules
{
	GENERATED_BODY()

public:

	virtual void SetupMatch() override;
	
	virtual void BindRaceDelegates() override;
	
	void SetTeam(ETeams NewTeam, bool IsVisitor);

	void CreateRacerManagers(TArray<UTeamManager*> TeamManagersRef);//!!!!!!!!!!!!!!!!

	UScoreManager* GetScoreManager() const;
	
	FTeamMatchData* GetTeamData(bool Status);

	FOnRacerManagersCreated OnRacerManagersCreatedDelegate;
	
private:

	void PopulateRacers(TArray<UTeamManager*> TeamManagersRef);///!!!!!!!!!

	virtual void HandleRaceFinished() override;

	UPROPERTY()
	TObjectPtr<UScoreManager> ScoreManager;
	
	TArray<FTeamMatchData> Teams;
};
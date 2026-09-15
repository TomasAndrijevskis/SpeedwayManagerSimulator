
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/Rules/ERaceResults.h"
#include "RacerStatsLine_Base.generated.h"


class URacerMatchManager;
class UHorizontalBox;
class UNumbersBox;

UCLASS()
class SMS_API URacerStatsLine_Base : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetID(int32 NewID);

	int GetID() const;

	virtual void InitializeManagers(URacerMatchManager* RacerManagerRef);
	
protected:

	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_RacerNumber;
	
	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_OverallPoints;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HB_Points;

	int32 RacerStatsLineID;
	
private:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UNumbersBox> PointsBoxClass;

	void CreateNewPointsBox(const ERaceResults& RaceResult, bool AddBonus);

	void UpdateOverallPoints(int32 Points, int32 Bonus);

	void BindDelegates();

	UPROPERTY()
	URacerMatchManager* RacerManager;
};

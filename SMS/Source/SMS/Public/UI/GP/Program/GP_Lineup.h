
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GP_Lineup.generated.h"


class URacerMatchManager;
class UGP_RacerStatsLine;
class UVerticalBox;

UCLASS()
class SMS_API UGP_Lineup : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION()
	void SortLines();
	
protected:

	virtual void NativeConstruct() override;
	
private:

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VB_TopRacers;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VB_BottomRacers;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGP_RacerStatsLine> RacerStatsLineClass;

	void CreateRacerStatsLines();

	UGP_RacerStatsLine* CreateRacerStatsLine(const TObjectPtr<URacerMatchManager>& RacerManager, int Position);
	
	void MoveRacerStatsLine(UGP_RacerStatsLine* RacerStatsLine, int32 Position, int32 RacersCount);

	void AddRacerStatsLine(UGP_RacerStatsLine* RacerStatsLine, int32 Position, int32 Amount);
	
	UPROPERTY()
	TArray<UGP_RacerStatsLine*> RacerStatsLines;
};

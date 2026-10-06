
#pragma once

#include "CoreMinimal.h"
#include "Data/Locations/CityData.h"
#include "Data/Locations/ECities.h"
#include "Data/Locations/ECountries.h"
#include "UI/BaseClasses/CalendarLine_Base.h"
#include "GP_CalendarLine.generated.h"


class UTrackDataAsset;
class ULocationsDataAsset;

UCLASS()
class SMS_API UGP_CalendarLine : public UCalendarLine_Base
{
	GENERATED_BODY()

public:

	void InitializeLine(ECountries Country, int32 NewRound);

	void SetRound(int32 NewRound);
	
protected:

	UPROPERTY(meta = (BindWidget))
	UNamesBox* NamesBox_Country;

	UPROPERTY(meta = (BindWidget))
	UNamesBox* NamesBox_City;
	
	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_Round;

	UPROPERTY(EditDefaultsOnly)
	ULocationsDataAsset* LocationsDataAsset;

private:

	virtual void CollectMatchScore() override;

	virtual void OnMatchEnded() override;

	virtual void StartMatch() override;

	void SetLocation(ECountries Location, ECities City);

	void GetLocation(ECities& OutCity, FCityData& OutCityData, const ECountries Country);
	
	UPROPERTY()
	UTrackDataAsset* TrackData;

	int32 Round = 0;
};

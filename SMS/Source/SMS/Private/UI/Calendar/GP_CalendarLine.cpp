
#include "UI/Calendar/GP_CalendarLine.h"
#include "Components/Button.h"
#include "Data/Locations/LocationsDataAsset.h"
#include "UI/BaseClasses/NamesBox.h"
#include "UI/BaseClasses/NumbersBox.h"


void UGP_CalendarLine::InitializeLine(ECountries Location, int32 NewRound)
{
	SetRound(NewRound);
	if (!LocationsDataAsset) return;
	ECities City = ECities::None;
	FCityData CityData;
	for (const auto& Country : LocationsDataAsset->Locations)
	{
		if (Country.Key == Location)
		{
			for (const auto& c : Country.Value.City)
			{
				City = c.Key;
				CityData = c.Value;
			}
			break;
		}
	}
	SetLocation(Location, City);
	TrackData = CityData.TrackData;
}


void UGP_CalendarLine::StartMatch()
{
	
}


void UGP_CalendarLine::OnMatchEnded()
{
	Button_StartMatch->OnClicked.Clear();
	Button_StartMatch->SetIsEnabled(false);
}


void UGP_CalendarLine::CollectMatchScore()
{
	
}


void UGP_CalendarLine::SetLocation(ECountries Location, ECities City)
{
	NamesBox_Country->SetText(UEnum::GetDisplayValueAsText(Location));
	NamesBox_City->SetText(UEnum::GetDisplayValueAsText(City));
}


void UGP_CalendarLine::SetRound(int32 NewRound)
{
	Round = NewRound;
	NumbersBox_Round->SetText(Round);
}
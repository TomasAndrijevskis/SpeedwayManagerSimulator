
#include "UI/Calendar/GP_CalendarLine.h"
#include "Data/Locations/LocationsDataAsset.h"
#include "Rules/GP_Rules.h"
#include "Subsystems/MatchManagerSubsystem.h"
#include "UI/BaseClasses/NamesBox.h"
#include "UI/BaseClasses/NumbersBox.h"
#include "UI/BaseClasses/Program_Base.h"


void UGP_CalendarLine::InitializeLine(ECountries Country, int32 NewRound)
{
	SetRound(NewRound);
	if (!LocationsDataAsset) return;
	ECities City = ECities::None;
	FCityData CityData;
	GetLocation(City, CityData, Country);
	SetLocation(Country, City);
	TrackData = CityData.TrackData;
	OnMatchCreated();
}


void UGP_CalendarLine::StartMatch()
{
	if (UMatchManagerSubsystem* MatchManagerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMatchManagerSubsystem>())
	{
		MatchManagerSubsystem->StartMatch(UGP_Rules::StaticClass());
		MatchManagerSubsystem->GetCompetitionRules()->OnRacingFinishedDelegate.AddUObject(this, &UGP_CalendarLine::CollectMatchScore);
		if (!ProgramClass) return;
		UProgram* Program = CreateWidget<UProgram>(this, ProgramClass);
		if (!Program) return;
		Program->AddToViewport(1);
	}
}


void UGP_CalendarLine::CollectMatchScore()
{
	UE_LOG(LogTemp, Warning, TEXT("CollectMatchScore"));
	OnMatchEnded();
}


void UGP_CalendarLine::OnMatchEnded()
{
	Super::OnMatchEnded();
}


void UGP_CalendarLine::SetLocation(ECountries Location, ECities City)
{
	NamesBox_Country->SetText(UEnum::GetDisplayValueAsText(Location));
	NamesBox_City->SetText(UEnum::GetDisplayValueAsText(City));
}


void UGP_CalendarLine::GetLocation(ECities& OutCity, FCityData& OutCityData, const ECountries Country)
{
	for (const auto& Location : LocationsDataAsset->Locations)
	{
		if (Location.Key == Country)
		{
			for (const auto& c : Location.Value.City)
			{
				OutCity = c.Key;
				OutCityData = c.Value;
			}
			break;
		}
	}
}


void UGP_CalendarLine::SetRound(int32 NewRound)
{
	Round = NewRound;
	NumbersBox_Round->SetText(Round);
}

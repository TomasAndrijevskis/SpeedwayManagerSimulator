
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/Calendar/ECompetitionType.h"
#include "Data/Calendar/MatchData.h"
#include "Data/Calendar/MatchID.h"
#include "Data/Calendar/TeamsInMatch.h"
#include "Data/Locations/ECountries.h"
#include "CalendarWeek.generated.h"


class UGP_CalendarLine;
class ULeague_CalendarLine;
class UVerticalBox;
class UNumbersBox;
class UButton;

UCLASS()
class SMS_API UCalendarWeek : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetWeek(int32 NewWeek);

	void CreateMatches(const TArray<FTeamsInMatch>& Matches, FMatchData& MatchData);

	void CreateMatch(ECountries Location, int32 Round, const FMatchData& MatchData);
	
private:
	
	UPROPERTY(meta = (BindWidget))
	UNumbersBox* NumbersBox_Round;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VerticalBox_Content;
	
	ULeague_CalendarLine* CreateMatch(int32 HomeTeamID, int32 VisitorTeamID, const FMatchData& MatchData);
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ULeague_CalendarLine> League_CalendarLineClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGP_CalendarLine> GP_CalendarLineClass;
	
};

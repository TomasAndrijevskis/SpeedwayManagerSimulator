
#include "UI/BaseClasses/CalendarLine_Base.h"
#include "Components/Button.h"
#include "UI/BaseClasses/NamesBox.h"


void UCalendarLine_Base::NativeConstruct()
{
	Super::NativeConstruct();
	Button_StartMatch->OnClicked.AddUniqueDynamic(this, &UCalendarLine_Base::StartMatch);
}

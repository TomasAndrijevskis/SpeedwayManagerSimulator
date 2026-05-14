
#include "UI/BaseClasses/NamesBox.h"
#include "Components/TextBlock.h"


void UNamesBox::SetName(const FString& NewName)
{
	Text_Name->SetText(FText::FromString(NewName));
}

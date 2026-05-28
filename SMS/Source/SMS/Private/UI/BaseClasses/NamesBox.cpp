
#include "UI/BaseClasses/NamesBox.h"
#include "Components/TextBlock.h"


void UNamesBox::SetText(const FString& NewName)
{
	Text_Name->SetText(FText::FromString(NewName));
}


void UNamesBox::SetText(const FText& NewText)
{
	Text_Name->SetText(NewText);
}

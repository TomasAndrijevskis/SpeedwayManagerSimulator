
#include "UI/BaseClasses/NamesBox.h"
#include "Components/TextBlock.h"


void UNamesBox::NativeConstruct()
{
	Super::NativeConstruct();
	if (SetTextInEditor) SetText(TextFromEditor);
}


void UNamesBox::SetText(const FString& NewName)
{
	Text_Name->SetText(FText::FromString(NewName));
}


void UNamesBox::SetText(const FText& NewText)
{
	Text_Name->SetText(NewText);
}
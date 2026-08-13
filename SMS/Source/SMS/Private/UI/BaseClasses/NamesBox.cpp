
#include "UI/BaseClasses/NamesBox.h"

#include "Components/SizeBox.h"
#include "Components/TextBlock.h"


void UNamesBox::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (SetTextInEditor) SetText(TextFromEditor);
	if (bOverrideSize)
	{
		SizeBox_Content->SetWidthOverride(NewSize.X);
		SizeBox_Content->SetHeightOverride(NewSize.Y);
	}
}


void UNamesBox::SetText(const FString& NewName)
{
	Text_Name->SetText(FText::FromString(NewName));
}


void UNamesBox::SetText(const FText& NewText)
{
	Text_Name->SetText(NewText);
}
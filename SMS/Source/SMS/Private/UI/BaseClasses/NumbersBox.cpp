
#include "UI/BaseClasses/NumbersBox.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"


void UNumbersBox::NativeConstruct()
{
	Super::NativeConstruct();
	if (OverrideFontSize) ChangeTextSize();
}


void UNumbersBox::ChangeTextSize()
{
	FSlateFontInfo NewFont = Text->GetFont();
	NewFont.Size = FontSize;
	Text->SetFont(NewFont);
}


void UNumbersBox::SetText(const FString& NewText)
{
	Text->SetText(FText::FromString(NewText));
}


void UNumbersBox::SetColour(const FColor& NewColour)
{
	Border_BackgroundColour->SetBrushColor(NewColour);
}


int UNumbersBox::GetNumber()
{
	FString NumberText = Text->GetText().ToString();
	if (NumberText.IsNumeric())
	{
		return FCString::Atoi(*NumberText);
	}
	return 0;
}
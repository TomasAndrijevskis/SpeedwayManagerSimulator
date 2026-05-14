
#include "UI/BaseClasses/NumbersBox.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"


void UNumbersBox::SetNumber(const FString& Number)
{
	Text_Number->SetText(FText::FromString(Number));
}


void UNumbersBox::SetColour(const FColor& NewColour)
{
	Border_BackgroundColour->SetBrushColor(NewColour);
}


int UNumbersBox::GetNumber()
{
	FString NumberText = Text_Number->GetText().ToString();
	if (NumberText.IsNumeric())
	{
		return FCString::Atoi(*NumberText);
	}
	return 0;
}

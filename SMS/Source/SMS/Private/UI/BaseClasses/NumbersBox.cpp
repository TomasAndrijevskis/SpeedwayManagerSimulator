
#include "UI/BaseClasses/NumbersBox.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Data/RaceData/EHelmetColour.h"


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


void UNumbersBox::SetText(int NewText)
{
	Text->SetText(FText::FromString(FString::FromInt(NewText)));
}


void UNumbersBox::SetColour(const EHelmetColour& NewColour)
{
	Border_BackgroundColour->SetBrushColor(HelmetColours::GetHelmetColour(NewColour));
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


const FString& UNumbersBox::GetNumberAsString() const
{
	return Text->GetText().ToString();
}


void UNumbersBox::AddNumber(int AddNumber)
{
	int CurrentNumber = GetNumber();
	CurrentNumber += AddNumber;
	SetText(CurrentNumber);
}

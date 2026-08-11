
#include "UI/BaseClasses/NumbersBox.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Data/RaceData/EHelmetColour.h"


void UNumbersBox::NativeConstruct()
{
	Super::NativeConstruct();
	if (OverrideFontSize) ChangeTextSize();
	if (SetTextInEditor) SetText(TextFromEditor);
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


void UNumbersBox::SetText(int32 NewText)
{
	Text->SetText(FText::FromString(FString::FromInt(NewText)));
}

void UNumbersBox::SetText(float NewText)
{
	Text->SetText(FText::FromString(FString::Printf(TEXT("%.2f"), NewText)));
}


void UNumbersBox::SetText(FText NewText)
{
	Text->SetText(NewText);
}


void UNumbersBox::SetColour(const EHelmetColour& NewColour)
{
	Border_BackgroundColour->SetBrushColor(HelmetColours::GetHelmetColour(NewColour));
}


int32 UNumbersBox::GetNumber()
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


void UNumbersBox::AddNumber(int32 AddNumber)
{
	int32 CurrentNumber = GetNumber();
	CurrentNumber += AddNumber;
	SetText(CurrentNumber);
}


#include "UI/BaseClasses/ChooseBox.h"
#include "Components/ComboBoxString.h"


void UChooseBox::NativeConstruct()
{
	Super::NativeConstruct();
	ComboBox->OnSelectionChanged.AddUniqueDynamic(this, &UChooseBox::OnSelectionChanged);
}


void UChooseBox::OnSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	OnSelectionChangedDelegate.Broadcast(SelectedItem, SelectionType);
}


void UChooseBox::AddOption(const FString& Option)
{
	ComboBox->AddOption(Option);
}


void UChooseBox::RemoveOption(const FString& Option)
{
	ComboBox->RemoveOption(Option);
}


int UChooseBox::GetNumberOfOptions() const
{
	return ComboBox->GetOptionCount();
}


FString UChooseBox::GetSelectedOptionAtIndex(int Index) const
{
	return ComboBox->GetOptionAtIndex(Index);
}


void UChooseBox::SetRandomOption(const FString& RandomOption)
{
	ComboBox->SetSelectedOption(RandomOption);
}


bool UChooseBox::AnyOptionsLeft() const
{
	return ComboBox->GetOptionCount() > 0;
}


void UChooseBox::MakeChooseBoxUnavailable()
{
	ComboBox->SetVisibility(ESlateVisibility::HitTestInvisible);
}


bool UChooseBox::DoesOptionExists(const FString& OptionName) const
{
	for (int32 i = 0; i < ComboBox->GetOptionCount(); i++)
	{
		if (OptionName == ComboBox->GetOptionAtIndex(i)) return true;
	}
	return false;
}
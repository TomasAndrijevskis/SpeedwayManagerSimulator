
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


void UChooseBox::AddOption(const FString& NewOption)
{
	ComboBox->AddOption(NewOption);
}


void UChooseBox::RemoveOption(const FString& NewOption)
{
	ComboBox->RemoveOption(NewOption);
}


int UChooseBox::GetNumberOfOptions() const
{
	return ComboBox->GetOptionCount();
}


FString UChooseBox::GetSelectedOption(int Index) const
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


void UChooseBox::ChangeStatus()
{
	ComboBox->SetVisibility(ESlateVisibility::HitTestInvisible);
}
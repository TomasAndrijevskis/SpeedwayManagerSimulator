
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
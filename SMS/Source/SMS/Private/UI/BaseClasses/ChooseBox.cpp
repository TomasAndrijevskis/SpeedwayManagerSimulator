
#include "UI/BaseClasses/ChooseBox.h"
#include "Components/ComboBoxString.h"


void UChooseBox::NativeConstruct()
{
	Super::NativeConstruct();
	ComboBox->OnSelectionChanged.AddUniqueDynamic(this, &UChooseBox::OnSelectionChanged);
	FillComboBox();
}


void UChooseBox::OnSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	OnSelectionChangedDelegate.Broadcast(SelectedItem, SelectionType);
}


void UChooseBox::FillComboBox()
{
	ComboBox->AddOption("Tomas");
	ComboBox->AddOption("Ivars");
	ComboBox->AddOption("Mareks");
	ComboBox->AddOption("Ediks");
}
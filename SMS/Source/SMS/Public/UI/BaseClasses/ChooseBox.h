
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChooseBox.generated.h"

class UComboBoxString;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSelectionChanged, FString, ESelectInfo::Type);
UCLASS()
class SMS_API UChooseBox : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION()
	void OnSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);
	
	FOnSelectionChanged OnSelectionChangedDelegate;

protected:

	virtual void NativeConstruct() override;
	
private:

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* ComboBox;

	void FillComboBox();
};

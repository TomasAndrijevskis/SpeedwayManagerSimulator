
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
	
	void AddOption(const FString& Option);

	void RemoveOption(const FString& Option);
	
	int GetNumberOfOptions() const;

	FString GetSelectedOptionAtIndex(int Index) const;
	
	void SetRandomOption(const FString& RandomOption);

	bool AnyOptionsLeft() const;

	void DisableChooseBox();

	bool DoesOptionExists(const FString& OptionName) const;

	bool IsAnyOptionChosen() const;

	void ClearSelection();
	
	FOnSelectionChanged OnSelectionChangedDelegate;

protected:

	virtual void NativeConstruct() override;
	
private:

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* ComboBox;

	UFUNCTION()
	void OnSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);
};

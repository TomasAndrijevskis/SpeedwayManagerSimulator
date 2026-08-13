
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NamesBox.generated.h"

class USizeBox;
class UTextBlock;

UCLASS()
class SMS_API UNamesBox : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetText(const FString& NewName);

	void SetText(const FText& NewText);

protected:

	virtual void NativePreConstruct() override;
	
private:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Name;

	UPROPERTY(meta = (BindWidget))
	USizeBox* SizeBox_Content;
	
	UPROPERTY(EditAnywhere)
	bool SetTextInEditor = false;
	
	UPROPERTY(EditAnywhere, meta = (EditCondition = "SetTextInEditor"))
	FText TextFromEditor;

	UPROPERTY(EditAnywhere)
	bool bOverrideSize = false;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "bOverrideSize"))
	FVector2D NewSize = {150,40}; //default size
};

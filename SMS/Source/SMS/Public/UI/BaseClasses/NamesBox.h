
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NamesBox.generated.h"

class UTextBlock;

UCLASS()
class SMS_API UNamesBox : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetText(const FString& NewName);

	void SetText(const FText& NewText);
	
private:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Name;
};

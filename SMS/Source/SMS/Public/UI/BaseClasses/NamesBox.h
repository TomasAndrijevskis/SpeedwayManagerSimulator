
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

	void SetName(const FString& NewName);
	
private:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Name;
};

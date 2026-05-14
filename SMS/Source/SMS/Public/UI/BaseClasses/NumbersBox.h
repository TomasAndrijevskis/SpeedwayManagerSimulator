
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NumbersBox.generated.h"

class UBorder;
class UTextBlock;

UCLASS()
class SMS_API UNumbersBox : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetNumber(const FString& Number);

	void SetColour(const FColor& NewColour);
	
private:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Number;

	UPROPERTY(meta = (BindWidget))
	UBorder* Border_BackgroundColour;
};

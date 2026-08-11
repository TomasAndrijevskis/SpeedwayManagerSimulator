
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/RaceData/EHelmetColour.h"
#include "NumbersBox.generated.h"

class UBorder;
class UTextBlock;

UCLASS()
class SMS_API UNumbersBox : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetText(const FString& NewText);

	void SetText(int32 NewText);

	void SetText(float NewText);
	
	void SetText(FText NewText);
	
	void SetColour(const EHelmetColour& NewColour);

	int32 GetNumber();

	const FString& GetNumberAsString() const;
	
	void AddNumber(int32 AddNumber);
	
protected:

	virtual void NativeConstruct() override;
	
private:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text;

	UPROPERTY(meta = (BindWidget))
	UBorder* Border_BackgroundColour;

	void ChangeTextSize();
	
	UPROPERTY(EditAnywhere)
	bool OverrideFontSize = false;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "OverrideFontSize"))
	float FontSize = 0;

	UPROPERTY(EditAnywhere)
	bool SetTextInEditor = false;
	
	UPROPERTY(EditAnywhere, meta = (EditCondition = "SetTextInEditor"))
	FText TextFromEditor;
};
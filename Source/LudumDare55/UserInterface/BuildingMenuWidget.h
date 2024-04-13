// Made by Titled Goose Team during Ludum Dare 55

#pragma once

#include "CoreMinimal.h"
#include "BaseUserWidget.h"

#include "BuildingMenuWidget.generated.h"

class UHorizontalBox;
class UButtonWidget;
/**
 * 
 */
UCLASS()
class LUDUMDARE55_API UBuildingMenuWidget : public UBaseUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;

	virtual void NativePreConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void ShowButtons();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UHorizontalBox> HorizontalBox_Buttons = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UButtonWidget> Button_Quit = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<UButtonWidget>> ButtonClasses = {};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<UButtonWidget>> Buttons;
	
	UPROPERTY(BlueprintReadOnly)
	float SpaceBetweenButtons = 15.f;

	UFUNCTION()
	void HandleButtonClicked(UButtonWidget* ButtonWidget);

	void SetButtonsVisibility(const bool bIsVisible);
};

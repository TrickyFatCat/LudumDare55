// Made by Titled Goose Team during Ludum Dare 55

#pragma once

#include "CoreMinimal.h"
#include "BaseUserWidget.h"
#include "LudumDare55/Gameplay/Building.h"

#include "BuildingMenuWidget.generated.h"

class UBuildingButtonWidget;
class ABuilding;
class UHorizontalBox;
class UButtonWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonsShowedDynamicSignature);
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
	UPROPERTY(BlueprintAssignable)
	FOnButtonsShowedDynamicSignature OnButtonsShowed;
	
	UFUNCTION(BlueprintCallable)
	void ShowButtons();

	UFUNCTION(BlueprintCallable)
	void SetOwningBuilding(ABuilding* Building);

protected:
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
	// TObjectPtr<UHorizontalBox> HorizontalBox_Buttons = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UBuildingButtonWidget> Button_Quit = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<UBuildingButtonWidget>> ButtonClasses = {};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<UBuildingButtonWidget>> Buttons;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ABuilding> OwningBuilding = nullptr;
	
	UPROPERTY(BlueprintReadOnly)
	float SpaceBetweenButtons = 15.f;

	UFUNCTION()
	void HandleButtonClicked(UButtonWidget* ButtonWidget);

	void SetButtonsVisibility(const bool bIsVisible);
private:
	void GenerateButtons();
};

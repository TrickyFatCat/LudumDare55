// Made by Titled Goose Team during Ludum Dare 55

#pragma once

#include "CoreMinimal.h"
#include "ButtonWidget.h"
#include "BuildingButtonWidget.generated.h"

class ABuilding;
/**
 * 
 */
UCLASS()
class LUDUMDARE55_API UBuildingButtonWidget : public UButtonWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetOwningBuilding(ABuilding* Building) { OwningBuilding = Building; }
protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ABuilding> OwningBuilding = nullptr;
};

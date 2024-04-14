// Made by Titled Goose Team during Ludum Dare 55

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Building.generated.h"

class UBuildingMenuWidget;
class UWidgetComponent;
class UStaticMeshComponent;

UCLASS()
class LUDUMDARE55_API ABuilding : public AActor
{
	GENERATED_BODY()

public:
	ABuilding();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> SceneComponent = nullptr;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> MeshComponent = nullptr;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> MenuWidgetComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UBuildingMenuWidget> BuildingMenuWidget = nullptr;

	UPROPERTY(BlueprintReadOnly)
	bool bIsSelected = false;

	UFUNCTION()
	void HandleMouseClick(AActor* TouchedActor, FKey ButtonPressed);

private:
	void SetWidgetVisibility(const bool bIsVisible);

	UFUNCTION()
	void HandleBeginCursorOver(AActor* TouchedActor);

	UFUNCTION()
	void HandleEndCursorOver(AActor* TouchedActor);
};

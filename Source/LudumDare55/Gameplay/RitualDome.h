// Made by Titled Goose Team during Ludum Dare 55

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RitualDome.generated.h"

class USphereComponent;
class UHitPointsComponent;

UCLASS()
class LUDUMDARE55_API ARitualDome : public AActor
{
	GENERATED_BODY()

public:
	ARitualDome();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess))
	TObjectPtr<USphereComponent> Collision = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess))
	TObjectPtr<UHitPointsComponent> HitPointsComponent = nullptr;

	UFUNCTION()
	void HandleZeroHitPoints();
};

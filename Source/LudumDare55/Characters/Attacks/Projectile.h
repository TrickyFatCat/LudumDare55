// Made by Titled Goose Team during Ludum Dare 55

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHitSignature);

UCLASS()
class LUDUMDARE55_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	AProjectile();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USphereComponent> SphereComponent;

	UPROPERTY(BlueprintAssignable)
	FOnHitSignature OnHit;

public:
	auto SetProjectileData(const FVector& Direction, const int32 Damage) -> void;

private:
	FVector MovementDirection = FVector::ForwardVector;

	int32 Damage = 1;

	UFUNCTION()
	void HandleProjectileHit(UPrimitiveComponent* HitComponent,
	                         AActor* OtherActor,
	                         UPrimitiveComponent* OtherComp,
	                         FVector NormalImpulse,
	                         const FHitResult& Hit);
};

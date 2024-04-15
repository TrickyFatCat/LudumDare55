// Made by Titled Goose Team during Ludum Dare 55

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

class UCharacterDeathComponent;
class UEnemySoulComponent;
class UHitPointsComponent;

UCLASS()
class LUDUMDARE55_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemy();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UHitPointsComponent> HitPointsComponent = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UEnemySoulComponent> EnemySoulComponent = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UCharacterDeathComponent> CharacterDeathComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FName> BonesToHide;

	UFUNCTION()
	void HandleAnyDamageTaken(AActor* DamagedActor,
	                          float Damage,
	                          const UDamageType* DamageType,
	                          AController* InstigatedBy,
	                          AActor* DamageCauser);

	UFUNCTION()
	void HandleZeroHealth();
};

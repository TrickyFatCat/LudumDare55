// Made by Titled Goose Team during Ludum Dare 55

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterAttackComponent.generated.h"

class AProjectile;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackStartedDynamicSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAtackFinishedDynamicSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackInitiatedDynamicSignature);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUDUMDARE55_API UCharacterAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCharacterAttackComponent();

protected:
	virtual void InitializeComponent() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* AnimMontage = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Range = 200.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Damage = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AProjectile> ProjectileClass = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 ProjectilesPerAttack = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AttackAngle = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector AttackOffset = FVector::Zero();

public:
	UPROPERTY(BlueprintAssignable)
	FOnAttackStartedDynamicSignature OnAttackStarted;

	UPROPERTY(BlueprintAssignable)
	FOnAtackFinishedDynamicSignature OnAttackFinished;

	UPROPERTY(BlueprintAssignable)
	FOnAttackInitiatedDynamicSignature OnAttackInitiated;
	
	UFUNCTION(BlueprintCallable)
	void StartAttack();

	UFUNCTION(BlueprintCallable)
	void FinishAttack();

	UFUNCTION(BlueprintCallable)
	void InitiateAttack();
	
private:
	UPROPERTY()
	ACharacter* Character = nullptr;
};

// Made by Titled Goose Team during Ludum Dare 55

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterAttackComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackStartedDynamicSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAtackFinishedDynamicSignature);

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

public:
	UPROPERTY(BlueprintAssignable)
	FOnAttackStartedDynamicSignature OnAttackStarted;

	UPROPERTY(BlueprintAssignable)
	FOnAtackFinishedDynamicSignature OnAttackFinished;
	
	UFUNCTION(BlueprintCallable)
	void StartAttack();

	UFUNCTION(BlueprintCallable)
	void FinishAttack();
	
private:
	UPROPERTY()
	ACharacter* Character = nullptr;
};

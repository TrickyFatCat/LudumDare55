﻿// Made by Titled Goose Team during Ludum Dare 55

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Minion.generated.h"

class UCharacterAttackComponent;
class UCharacterDeathComponent;
class UMinionsCounterComponent;
class UMinionLifeTimeComponent;
class UHitPointsComponent;

UCLASS()
class LUDUMDARE55_API AMinion : public ACharacter
{
	GENERATED_BODY()

public:
	AMinion();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UHitPointsComponent> HitPointsComponent = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UMinionLifeTimeComponent> LifeTimeComponent = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UCharacterDeathComponent> CharacterDeathComponent = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UCharacterAttackComponent> CharacterAttackComponent = nullptr;

	UPROPERTY()
	TObjectPtr<UMinionsCounterComponent> CounterComponent = nullptr;

	UFUNCTION(BlueprintCallable)
	void DecrementCounter();

	UFUNCTION()
	void HandleZeroHealth();

	UFUNCTION()
	void HandleLifeExpired();
};

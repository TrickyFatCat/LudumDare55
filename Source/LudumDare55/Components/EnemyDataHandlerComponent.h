﻿// Made by Titled Goose Team during Ludum Dare 55

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyDataHandlerComponent.generated.h"


class AEnemy;
class AProjectile;

USTRUCT(BlueprintType)
struct FEnemyData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AEnemy> EnemyClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1", UIMin = "1"))
	int32 HitPoints = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1", UIMin = "1"))
	int32 Speed = 600;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1", UIMin = "1"))
	float AttackRange = 200.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1", UIMin = "1"))
	int32 Damage = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1", UIMin = "1"))
	int32 ProjectilesPerAttack = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1", UIMin = "1"))
	float AttackAngle = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* AttackAnimMontage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AProjectile> ProjectileClass = nullptr;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUDUMDARE55_API UEnemyDataHandlerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UEnemyDataHandlerComponent();

protected:
	virtual void InitializeComponent() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UDataTable* EnemyDataTable = nullptr;
};

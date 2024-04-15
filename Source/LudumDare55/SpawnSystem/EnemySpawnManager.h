// Made by Titled Goose Team during Ludum Dare 55

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScalableFloat.h"
#include "EnemySpawnManager.generated.h"

class AEnemySpawnPoint;
class AEnemy;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWaveStartedDynamicSignature, int32, Index);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWaveFinishedDynamicSignature, int32, Index);

USTRUCT(BlueprintType)
struct FEnemyWaveData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	TSubclassOf<AEnemy> Enemy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy", meta = (ClampMin = "1", UIMin = "1"))
	int32 Weight = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy", meta = (ClampMin = "1", UIMin = "1"))
	int32 Count = 1;
};

USTRUCT(BlueprintType)
struct FWaveData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly)
	TArray<TSubclassOf<AEnemy>> Enemies;

	UPROPERTY(BlueprintReadOnly)
	int32 MaxEnemies = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 Spawned = 0;

	UPROPERTY(BlueprintReadOnly)
	float SpawnDelay = 1.f;

	UPROPERTY(BlueprintReadOnly)
	int32 MaxSpawnAtOnce = 1;
};


UCLASS()
class LUDUMDARE55_API AEnemySpawnManager : public AActor
{
	GENERATED_BODY()

public:
	AEnemySpawnManager();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnWaveStartedDynamicSignature OnWaveStarted;

	UPROPERTY(BlueprintAssignable)
	FOnWaveFinishedDynamicSignature OnWaveFinished;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat SpawnDelay;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat MaxSpawnAtOnce;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat WaveSpawnDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MinRandomWaveIndex = 15;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<UDataTable*> WaveTables;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 WaveIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsRandomSpawn = true;

	void RandomizeEnemies();

	UFUNCTION()
	void SpawnEnemy();

	UFUNCTION(BlueprintCallable)
	void StartWave();

	UFUNCTION(BlueprintCallable)
	void FinishWave();

	bool GenerateWaveData();

private:
	TArray<AEnemySpawnPoint*> EnemySpawnPoints;

	FWaveData CurrentWaveData;

	UPROPERTY()
	FTimerHandle SpawnDelayTimer;

	UPROPERTY()
	FTimerHandle WaveRestartDelayTimer;

	UFUNCTION()
	void HandleGameStateChanged(EGameModeState NewState);
};

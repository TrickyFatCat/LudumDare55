// Made by Titled Goose Team during Ludum Dare 55

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawnManager.generated.h"

class AEnemySpawnPoint;
class AEnemy;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWaveStartedDynamicSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWaveFinishedDynamicSignature);

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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* WaveTable;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnDelay = 2.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxSpawnAtOnce = 2;
	
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsRandomSpawn = true;
	
	void RandomizeEnemies();

	UFUNCTION()
	void SpawnEnemy();

	UFUNCTION(BlueprintCallable)
	void StartWave();

	UFUNCTION(BlueprintCallable)
	void FinishWave();

	void GenerateWaveData();
	
	
private:	
	TArray<AEnemySpawnPoint*> EnemySpawnPoints;

	FWaveData CurrentWaveData;

	UPROPERTY()
	FTimerHandle SpawnDelayTimer;
};

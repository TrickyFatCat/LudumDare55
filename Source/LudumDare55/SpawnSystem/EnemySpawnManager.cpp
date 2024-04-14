// Made by Titled Goose Team during Ludum Dare 55


#include "EnemySpawnManager.h"

#include "EnemySpawnPoint.h"
#include "Kismet/GameplayStatics.h"
#include "LudumDare55/Characters/Enemy.h"


AEnemySpawnManager::AEnemySpawnManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEnemySpawnManager::BeginPlay()
{
	Super::BeginPlay();

	EnemySpawnPoints.Reset();
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(this, AEnemySpawnPoint::StaticClass(), OutActors);

	for (const auto Actor : OutActors)
	{
		EnemySpawnPoints.Add(Cast<AEnemySpawnPoint>(Actor));
	}
}

void AEnemySpawnManager::RandomizeEnemies()
{
	if (bIsRandomSpawn)
	{
		const int32 LastIndex = EnemySpawnPoints.Num() - 1;

		for (int32 y = 0; y <= LastIndex; ++y)
		{
			const int32 Index = FMath::RandRange(y, LastIndex);
			if (y != Index)
			{
				EnemySpawnPoints.Swap(y, Index);
			}
		}
	}
}

void AEnemySpawnManager::SpawnEnemy()
{
	for (int32 i = 0; i < CurrentWaveData.MaxSpawnAtOnce; i++)
	{
		if (CurrentWaveData.MaxEnemies == CurrentWaveData.Spawned) break;
		
		RandomizeEnemies();
		
		for (AEnemySpawnPoint* SpawnPoint : EnemySpawnPoints)
		{
			if (SpawnPoint->Spawn(CurrentWaveData.Enemies[CurrentWaveData.Enemies.Num() - 1]))
			{
				CurrentWaveData.Spawned++;
				CurrentWaveData.Enemies.RemoveAt(CurrentWaveData.Enemies.Num() - 1);
				break;
			}
		}
	}

	FinishWave();
}

void AEnemySpawnManager::StartWave()
{
	GenerateWaveData();
	GetWorldTimerManager().SetTimer(SpawnDelayTimer, this, &AEnemySpawnManager::SpawnEnemy, CurrentWaveData.SpawnDelay,
	                                true);
	OnWaveStarted.Broadcast();
}

void AEnemySpawnManager::FinishWave()
{
	if (CurrentWaveData.Spawned < CurrentWaveData.MaxEnemies)
	{
		return;
	}

	GetWorldTimerManager().ClearTimer(SpawnDelayTimer);
	OnWaveFinished.Broadcast();
}

void AEnemySpawnManager::GenerateWaveData()
{
	TArray<TSubclassOf<AEnemy>> EnemyClasses;

	TArray<FEnemyWaveData*> AllEnemies;
	WaveTable->GetAllRows<FEnemyWaveData>("", AllEnemies);

	for (const FEnemyWaveData* EnemyStat : AllEnemies)
	{
		for (int i = 0; i < EnemyStat->Count; i++)
		{
			EnemyClasses.Add(EnemyStat->Enemy);
		}
	}

	const int32 LastIndex = EnemyClasses.Num() - 1;
	for (int32 i = 0; i <= LastIndex; ++i)
	{
		const int32 Index = FMath::RandRange(i, LastIndex);

		if (i != Index)
		{
			EnemyClasses.Swap(i, Index);
		}
	}

	CurrentWaveData.Enemies = EnemyClasses;
	CurrentWaveData.MaxEnemies = EnemyClasses.Num();
	CurrentWaveData.Spawned = 0;
	CurrentWaveData.SpawnDelay = SpawnDelay;
	CurrentWaveData.MaxSpawnAtOnce = MaxSpawnAtOnce;
}

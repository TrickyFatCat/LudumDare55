// Made by Titled Goose Team during Ludum Dare 55

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawnPoint.generated.h"

class AEnemy;
class UArrowComponent;
class USphereComponent;

UENUM(BlueprintType)
enum class ESpawnerState: uint8
{
	Ready = 0,
	InSpawn,
	Frozen,
	Block
};

UCLASS()
class LUDUMDARE55_API AEnemySpawnPoint : public AActor
{
	GENERATED_BODY()

public:
	AEnemySpawnPoint();

protected:
	virtual void BeginPlay() override;

public:
	bool Spawn(TSubclassOf<AEnemy> EnemyClass);

	UFUNCTION(BlueprintCallable)
	void Lock() { State = ESpawnerState::Block; };

	UFUNCTION(BlueprintCallable)
	void Unlock() { State = ESpawnerState::Ready; };

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USphereComponent> CollisionComponent = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UArrowComponent> ArrowComponent = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FreezingDuration = 1.0f;

private:
	UPROPERTY(EditAnywhere)
	ESpawnerState State = ESpawnerState::Ready;

	bool bIsBlocked = false;

	FTimerHandle FreezingTimerHandle;
	
	UFUNCTION()
	void HandleCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	                                 AActor* OtherActor,
	                                 UPrimitiveComponent* OtherComp,
	                                 int OtherBodyIndex,
	                                 bool bFromSweep,
	                                 const FHitResult& SweepResult
	);

	UFUNCTION()
	void HandleCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent,
	                               AActor* OtherActor,
	                               UPrimitiveComponent* OtherComp,
	                               int OtherBodyIndex
	);

	UFUNCTION()
	void RemoveFreeze(); 
};

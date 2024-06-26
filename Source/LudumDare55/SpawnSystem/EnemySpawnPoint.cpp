﻿// Made by Titled Goose Team during Ludum Dare 55


#include "EnemySpawnPoint.h"

#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "LudumDare55/Characters/Enemy.h"


AEnemySpawnPoint::AEnemySpawnPoint()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("Collision");
	SetRootComponent(CollisionComponent);

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>("ForwardVector");
	ArrowComponent->SetArrowLength(100.f);
	ArrowComponent->SetArrowSize(2);
	ArrowComponent->SetupAttachment(GetRootComponent());
}

void AEnemySpawnPoint::BeginPlay()
{
	Super::BeginPlay();
}

bool AEnemySpawnPoint::Spawn(TSubclassOf<AEnemy> EnemyClass)
{
	if (bIsBlocked || State != ESpawnerState::Ready || !EnemyClass)
	{
		return false;
	}

	State = ESpawnerState::InSpawn;
	FTransform SpawnTransform = GetActorTransform();
	AEnemy* Enemy = GetWorld()->SpawnActorDeferred<AEnemy>(EnemyClass, SpawnTransform);
	FVector SpawnLocation = SpawnTransform.GetLocation();
	SpawnLocation.Z += Enemy->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
	SpawnTransform.SetLocation(SpawnLocation);
	Enemy->FinishSpawning(SpawnTransform);

	if (!Enemy)
	{
		return false;
	}

	State = ESpawnerState::Frozen;
	GetWorldTimerManager().SetTimer(FreezingTimerHandle, this, &AEnemySpawnPoint::RemoveFreeze, FreezingDuration);
	return Enemy != nullptr;
}

void AEnemySpawnPoint::HandleCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent,
                                                   AActor* OtherActor,
                                                   UPrimitiveComponent* OtherComp,
                                                   int OtherBodyIndex,
                                                   bool bFromSweep,
                                                   const FHitResult& SweepResult)
{
	bIsBlocked = true;
}

void AEnemySpawnPoint::HandleCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent,
                                                 AActor* OtherActor,
                                                 UPrimitiveComponent* OtherComp,
                                                 int OtherBodyIndex)
{
	TArray<AActor*> OutOverlappingActors;
	GetOverlappingActors(OutOverlappingActors, {ACharacter::StaticClass()});
	
	if (OutOverlappingActors.Num() == 0)
	{
		bIsBlocked = false;
	}
}

void AEnemySpawnPoint::RemoveFreeze()
{
	if (State != ESpawnerState::Block)
	{
		State = ESpawnerState::Ready;
	};
}

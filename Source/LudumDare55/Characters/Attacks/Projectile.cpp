// Made by Titled Goose Team during Ludum Dare 55


#include "Projectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SetRootComponent(SphereComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
}

void AProjectile::BeginPlay()
{
	ProjectileMovementComponent->Velocity = MovementDirection * ProjectileMovementComponent->InitialSpeed;
	SphereComponent->IgnoreActorWhenMoving(GetOwner(), true);

	SphereComponent->OnComponentHit.AddDynamic(this, &AProjectile::HandleProjectileHit);
	
	Super::BeginPlay();
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::SetProjectileData(const FVector& Direction, const int32 NewDamage)
{
	MovementDirection = Direction;
	this->Damage = Damage <= 0 ? 1 : Damage;
}

void AProjectile::HandleProjectileHit(UPrimitiveComponent* HitComponent,
                                      AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp,
                                      FVector NormalImpulse,
                                      const FHitResult& Hit)
{
	if (OtherActor)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, nullptr, this, nullptr);
	}

	OnHit.Broadcast();
	Destroy();
}

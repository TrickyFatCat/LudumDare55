// Made by Titled Goose Team during Ludum Dare 55


#include "Enemy.h"

#include "LudumDare55/Components/EnemySoulComponent.h"
#include "LudumDare55/Components/HitPointsComponent.h"


AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	HitPointsComponent = CreateDefaultSubobject<UHitPointsComponent>("HitPoints");
	EnemySoulComponent = CreateDefaultSubobject<UEnemySoulComponent>("EnemySoul");
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (!BonesToHide.IsEmpty())
	{
		for (auto& BoneName : BonesToHide)
		{
			GetMesh()->HideBoneByName(BoneName, PBO_None);
		}
	}

	OnTakeAnyDamage.AddUniqueDynamic(this, &AEnemy::HandleAnyDamageTaken);
	HitPointsComponent->OnValueZero.AddUniqueDynamic(EnemySoulComponent, &UEnemySoulComponent::IncreaseSouls);
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemy::HandleAnyDamageTaken(AActor* DamagedActor,
                                  float Damage,
                                  const UDamageType* DamageType,
                                  AController* InstigatedBy,
                                  AActor* DamageCauser)
{
	HitPointsComponent->DecreaseValue(Damage);
}

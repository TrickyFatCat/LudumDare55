// Made by Titled Goose Team during Ludum Dare 55


#include "Enemy.h"

#include "LudumDare55/Components/CharacterAttackComponent.h"
#include "LudumDare55/Components/CharacterDeathComponent.h"
#include "LudumDare55/Components/EnemyDataHandlerComponent.h"
#include "LudumDare55/Components/EnemySoulComponent.h"
#include "LudumDare55/Components/HitPointsComponent.h"


AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	HitPointsComponent = CreateDefaultSubobject<UHitPointsComponent>("HitPoints");
	EnemySoulComponent = CreateDefaultSubobject<UEnemySoulComponent>("EnemySoul");
	CharacterDeathComponent = CreateDefaultSubobject<UCharacterDeathComponent>("CharacterDeath");
	CharacterAttackComponent = CreateDefaultSubobject<UCharacterAttackComponent>("CharacterAttack");
	EnemyDataHandlerComponent = CreateDefaultSubobject<UEnemyDataHandlerComponent>("DataHandler");
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

	// OnTakeAnyDamage.AddUniqueDynamic(this, &AEnemy::HandleAnyDamageTaken);
	HitPointsComponent->OnValueZero.AddUniqueDynamic(this, &AEnemy::HandleZeroHealth);
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AEnemy::IsDead()
{
	return HitPointsComponent->GetValue() == 0;
}

void AEnemy::HandleAnyDamageTaken(AActor* DamagedActor,
                                  float Damage,
                                  const UDamageType* DamageType,
                                  AController* InstigatedBy,
                                  AActor* DamageCauser)
{
	HitPointsComponent->DecreaseValue(Damage);
}

void AEnemy::HandleZeroHealth()
{
	EnemySoulComponent->IncreaseSouls();
	CharacterDeathComponent->StartDeathSequence();
	SetActorTickEnabled(false);
}

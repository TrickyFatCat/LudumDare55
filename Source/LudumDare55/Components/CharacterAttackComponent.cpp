// Made by Titled Goose Team during Ludum Dare 55


#include "CharacterAttackComponent.h"

#include "GameFramework/Character.h"
#include "LudumDare55/Characters/Attacks/Projectile.h"


UCharacterAttackComponent::UCharacterAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UCharacterAttackComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
	Character = Cast<ACharacter>(GetOwner());
}

void UCharacterAttackComponent::StartAttack()
{
	if (!Character || !AnimMontage)
	{
		return;
	}

	Character->PlayAnimMontage(AnimMontage);
	OnAttackStarted.Broadcast();
}

void UCharacterAttackComponent::FinishAttack()
{
	OnAttackFinished.Broadcast();
}

void UCharacterAttackComponent::InitiateAttack()
{
	if (!ProjectileClass)
	{
		return;
	}

	const FVector StartPoint = GetOwner()->GetActorLocation();
	const float Theta = FMath::DegreesToRadians(AttackAngle / ProjectilesPerAttack);
	const float Phi = FMath::DegreesToRadians(AttackAngle * 0.5) - Theta * 0.5;

	for (int32 i = 0; i < ProjectilesPerAttack; i++)
	{
		FVector Direction = GetOwner()->GetActorForwardVector();
		Direction = Direction.RotateAngleAxisRad(Theta * i - Phi, FVector::UpVector);
		const FTransform SpawnTransform(FRotator::ZeroRotator, StartPoint + Direction);
		AProjectile* Projectile = GetWorld()->SpawnActorDeferred<AProjectile>(ProjectileClass, SpawnTransform);

		if (Projectile)
		{
			Projectile->SetProjectileData(Direction, Damage);
			Projectile->SetOwner(GetOwner());
			Projectile->FinishSpawning(SpawnTransform);
		}
	}

	OnAttackInitiated.Broadcast();
}

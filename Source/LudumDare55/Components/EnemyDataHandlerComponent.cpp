// Made by Titled Goose Team during Ludum Dare 55


#include "EnemyDataHandlerComponent.h"

#include "CharacterAttackComponent.h"
#include "HitPointsComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "LudumDare55/Characters/Enemy.h"


UEnemyDataHandlerComponent::UEnemyDataHandlerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UEnemyDataHandlerComponent::InitializeComponent()
{
	Super::InitializeComponent();

	if (!GetOwner() || !GetWorld()->IsGameWorld())
	{
		return;
	}

	if (!EnemyDataTable || !GetOwner()->IsA(AEnemy::StaticClass()))
	{
		return;
	}

	TArray<FEnemyData*> EnemyData;
	EnemyDataTable->GetAllRows<FEnemyData>("", EnemyData);

	if (EnemyData.IsEmpty())
	{
		return;
	}

	auto Predicate = [&](const FEnemyData* TargetData)
	{
		return TargetData->EnemyClass == GetOwner()->GetClass();
	};
	
	FEnemyData* Data = *EnemyData.FindByPredicate(Predicate);

	if (!Data)
	{
		return;
	}

	AEnemy* OwningEnemy = Cast<AEnemy>(GetOwner());
	OwningEnemy->GetHitPointsComponent()->SetMaxValue(Data->HitPoints);
	OwningEnemy->GetCharacterMovement()->MaxWalkSpeed = Data->Speed;

	UCharacterAttackComponent* AttackComponent = OwningEnemy->GetAttackComponent();
	AttackComponent->Range = Data->AttackRange;
	AttackComponent->Damage = Data->Damage;
	AttackComponent->ProjectilesPerAttack = Data->ProjectilesPerAttack;
	AttackComponent->AttackAngle = Data->AttackAngle;
	AttackComponent->AnimMontage = Data->AttackAnimMontage;
	AttackComponent->ProjectileClass = Data->ProjectileClass;

}


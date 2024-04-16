// Made by Titled Goose Team during Ludum Dare 55


#include "MinionDataHandlerComponent.h"

#include "CharacterAttackComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HitPointsComponent.h"
#include "LudumDare55/Characters/Minion.h"


UMinionDataHandlerComponent::UMinionDataHandlerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UMinionDataHandlerComponent::InitializeComponent()
{
	Super::InitializeComponent();

	if (!GetOwner() || !GetWorld()->IsGameWorld())
	{
		return;
	}

	if (!MinionDataTable || !GetOwner()->IsA(AMinion::StaticClass()))
	{
		return;
	}

	TArray<FMinionData*> MinionData;
	MinionDataTable->GetAllRows<FMinionData>("", MinionData);

	if (MinionData.IsEmpty())
	{
		return;
	}

	auto Predicate = [&](const FMinionData* TargetData)
	{
		return TargetData->MinionClass == GetOwner()->GetClass();
	};
	
	FMinionData* Data = *MinionData.FindByPredicate(Predicate);

	if (!Data)
	{
		return;
	}

	AMinion* OwningMinion = Cast<AMinion>(GetOwner());
	OwningMinion->GetHitPointsComponent()->SetMaxValue(Data->HitPoints);
	OwningMinion->GetCharacterMovement()->MaxWalkSpeed = Data->Speed;

	UCharacterAttackComponent* AttackComponent = OwningMinion->GetAttackComponent();
	AttackComponent->Range = Data->AttackRange;
	AttackComponent->Damage = Data->Damage;
	AttackComponent->ProjectilesPerAttack = Data->ProjectilesPerAttack;
	AttackComponent->AttackAngle = Data->AttackAngle;
	AttackComponent->AnimMontage = Data->AttackAnimMontage;
	AttackComponent->ProjectileClass = Data->ProjectileClass;
}

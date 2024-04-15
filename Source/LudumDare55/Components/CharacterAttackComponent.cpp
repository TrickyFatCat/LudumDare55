// Made by Titled Goose Team during Ludum Dare 55


#include "CharacterAttackComponent.h"

#include "GameFramework/Character.h"


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

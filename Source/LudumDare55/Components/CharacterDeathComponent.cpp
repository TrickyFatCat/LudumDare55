// Made by Titled Goose Team during Ludum Dare 55


#include "CharacterDeathComponent.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


UCharacterDeathComponent::UCharacterDeathComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UCharacterDeathComponent::InitializeComponent()
{
	Super::InitializeComponent();

	Character = Cast<ACharacter>(GetOwner());
	
	if (!Character)
	{
		return;
	}

	AIController = Cast<AAIController>(Character->GetController());
}

void UCharacterDeathComponent::StartDeathSequence()
{
	if (!Character || !AIController || !AnimMontage)
	{
		return;
	}

	Character->GetMovementComponent()->StopMovementImmediately();
	Character->PlayAnimMontage(AnimMontage);
	AIController->GetBrainComponent()->StopLogic("");
}

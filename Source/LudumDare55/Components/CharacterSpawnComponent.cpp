// Made by Titled Goose Team during Ludum Dare 55


#include "CharacterSpawnComponent.h"

#include "GameFramework/Character.h"


UCharacterSpawnComponent::UCharacterSpawnComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterSpawnComponent::InitializeComponent()
{
	Super::InitializeComponent();

	Character = Cast<ACharacter>(GetOwner());
}

void UCharacterSpawnComponent::StartSpawn()
{
	if (!Character || !AnimMontage)
	{
		FinishSpawn();
	}
	else
	{
		Character->PlayAnimMontage(AnimMontage);
	}

	OnSpawnStarted.Broadcast();
}

void UCharacterSpawnComponent::FinishSpawn()
{
	OnSpawnFinished.Broadcast();
}

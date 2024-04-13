// Made by Titled Goose Team during Ludum Dare 55


#include "HitPointsComponent.h"

UHitPointsComponent::UHitPointsComponent()
{
	bWantsInitializeComponent = true;
}

void UHitPointsComponent::InitializeComponent()
{
	Super::InitializeComponent();

	GetOwner()->OnTakeAnyDamage.AddUniqueDynamic(this, &UHitPointsComponent::HandleAnyDamageTaken);
}

void UHitPointsComponent::HandleAnyDamageTaken(AActor* DamagedActor,
                                               float Damage,
                                               const UDamageType* DamageType,
                                               AController* InstigatedBy,
                                               AActor* DamageCauser)
{
	DecreaseValue(Damage);
}

// Made by Titled Goose Team during Ludum Dare 55


#include "MinionLifeTimeComponent.h"

#include "MinionsCounterComponent.h"


UMinionLifeTimeComponent::UMinionLifeTimeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMinionLifeTimeComponent::StopTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(LifeTimerHandle);
	OnLifeExpired.Broadcast();
}

void UMinionLifeTimeComponent::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(LifeTimerHandle, this, &UMinionLifeTimeComponent::HandleLifeExpired, LifeDuration);
}

void UMinionLifeTimeComponent::HandleLifeExpired()
{
	OnLifeExpired.Broadcast();
}

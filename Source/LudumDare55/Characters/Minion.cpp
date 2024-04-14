﻿// Made by Titled Goose Team during Ludum Dare 55


#include "Minion.h"

#include "Kismet/GameplayStatics.h"
#include "LudumDare55/Components/HitPointsComponent.h"
#include "LudumDare55/Components/MinionLifeTimeComponent.h"
#include "LudumDare55/Components/MinionsCounterComponent.h"


AMinion::AMinion()
{
	PrimaryActorTick.bCanEverTick = true;

	HitPointsComponent = CreateDefaultSubobject<UHitPointsComponent>("HitPoints");
	LifeTimeComponent = CreateDefaultSubobject<UMinionLifeTimeComponent>("LifeTime");
}

void AMinion::BeginPlay()
{
	Super::BeginPlay();

	CounterComponent = UGameplayStatics::GetPlayerPawn(this, 0)->GetComponentByClass<UMinionsCounterComponent>();
	LifeTimeComponent->OnLifeExpired.AddUniqueDynamic(this, &AMinion::DecrementCounter);
	HitPointsComponent->OnValueZero.AddUniqueDynamic(LifeTimeComponent, &UMinionLifeTimeComponent::StopTimer);
}

void AMinion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMinion::DecrementCounter()
{
	if (!CounterComponent)
	{
		return;
	}
	
	CounterComponent->DecrementCounter(GetClass());
}

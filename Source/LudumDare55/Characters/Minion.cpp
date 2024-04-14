// Made by Titled Goose Team during Ludum Dare 55


#include "Minion.h"

#include "LudumDare55/Components/HitPointsComponent.h"


AMinion::AMinion()
{
	PrimaryActorTick.bCanEverTick = true;

	HitPointsComponent = CreateDefaultSubobject<UHitPointsComponent>("HitPoints");
}

void AMinion::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMinion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Made by Titled Goose Team during Ludum Dare 55


#include "RitualDome.h"

#include "Components/SphereComponent.h"
#include "LudumDare55/Components/HitPointsComponent.h"


ARitualDome::ARitualDome()
{
	PrimaryActorTick.bCanEverTick = false;

	Collision = CreateDefaultSubobject<USphereComponent>("Collision");
	SetRootComponent(Collision);

	HitPointsComponent = CreateDefaultSubobject<UHitPointsComponent>("HitPoints");
}

void ARitualDome::BeginPlay()
{
	Super::BeginPlay();
}

void ARitualDome::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Made by Titled Goose Team during Ludum Dare 55


#include "RitualDome.h"

#include "TrickyGameModeBase.h"
#include "TrickyGameModeLibrary.h"
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

	HitPointsComponent->OnValueZero.AddUniqueDynamic(this, &ARitualDome::HandleZeroHitPoints);
}

void ARitualDome::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARitualDome::HandleZeroHitPoints()
{
	UTrickyGameModeLibrary::GetTrickyGameMode(this)->FinishSession(false);
}

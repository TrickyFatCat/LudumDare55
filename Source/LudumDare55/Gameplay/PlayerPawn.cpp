// Made by Titled Goose Team during Ludum Dare 55


#include "PlayerPawn.h"

#include "LudumDare55/Components/SoulsCounterComponent.h"


APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	SoulsCounterComponent = CreateDefaultSubobject<USoulsCounterComponent>("SoulsCounter");
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


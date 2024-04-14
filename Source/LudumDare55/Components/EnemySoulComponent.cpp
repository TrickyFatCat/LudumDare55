// Made by Titled Goose Team during Ludum Dare 55


#include "EnemySoulComponent.h"

#include "SoulsCounterComponent.h"
#include "Kismet/GameplayStatics.h"


UEnemySoulComponent::UEnemySoulComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UEnemySoulComponent::BeginPlay()
{
	Super::BeginPlay();

	APawn* Pawn = UGameplayStatics::GetPlayerPawn(this, 0);
	SoulsCounterComponent = Pawn->GetComponentByClass<USoulsCounterComponent>();
}

void UEnemySoulComponent::IncreaseSouls()
{
	if (!SoulsCounterComponent)
	{
		return;
	}

	SoulsCounterComponent->AddSouls(SoulsAmount);
}


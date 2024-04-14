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

bool UEnemySoulComponent::IncreaseSouls()
{
	if (!SoulsCounterComponent)
	{
		return false;
	}

	return SoulsCounterComponent->AddSouls(SoulsAmount);
}


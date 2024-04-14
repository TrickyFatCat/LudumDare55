// Made by Titled Goose Team during Ludum Dare 55


#include "MinionSpawnerComponent.h"

#include "Kismet/GameplayStatics.h"
#include "LudumDare55/Characters/Minion.h"


UMinionSpawnerComponent::UMinionSpawnerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UMinionSpawnerComponent::SpawnMinion(TSubclassOf<AMinion> MinionClass)
{
	if (!MinionClass)
	{
		return false;
	}

	AMinion* Minion = GetWorld()->SpawnActorDeferred<AMinion>(MinionClass, GetOwner()->GetTransform());
	Minion->FinishSpawning(GetOwner()->GetTransform());
	OnMinionSpawned.Broadcast(this, Minion);
	return true;
}

// Made by Titled Goose Team during Ludum Dare 55


#include "MinionSpawnerComponent.h"

#include "Components/CapsuleComponent.h"
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

	FVector SpawnLocation = GetOwner()->GetActorLocation();
	FTransform SpawnTransform {SpawnLocation};
	SpawnTransform.SetRotation(GetOwner()->GetActorRotation().Quaternion());
	
	AMinion* Minion = GetWorld()->SpawnActorDeferred<AMinion>(MinionClass, SpawnTransform);
	SpawnLocation.Z =  Minion->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	SpawnTransform.SetLocation(SpawnLocation);
	Minion->FinishSpawning(SpawnTransform);
	OnMinionSpawned.Broadcast(this, Minion);
	return true;
}

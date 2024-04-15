// Made by Titled Goose Team during Ludum Dare 55


#include "AnimNotify_FinishSpawn.h"

#include "LudumDare55/Components/CharacterSpawnComponent.h"

void UAnimNotify_FinishSpawn::Notify(USkeletalMeshComponent* MeshComp,
                                     UAnimSequenceBase* Animation,
                                     const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	UCharacterSpawnComponent* SpawnComponent = MeshComp->GetOwner()->GetComponentByClass<UCharacterSpawnComponent>();

	if (SpawnComponent)
	{
		SpawnComponent->FinishSpawn();
	}
}

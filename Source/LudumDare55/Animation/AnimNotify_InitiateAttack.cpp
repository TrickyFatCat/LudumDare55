// Made by Titled Goose Team during Ludum Dare 55


#include "AnimNotify_InitiateAttack.h"

#include "LudumDare55/Components/CharacterAttackComponent.h"


void UAnimNotify_InitiateAttack::Notify(USkeletalMeshComponent* MeshComp,
                                        UAnimSequenceBase* Animation,
                                        const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	UCharacterAttackComponent* AttackComponent = MeshComp->GetOwner()->GetComponentByClass<UCharacterAttackComponent>();

	if (AttackComponent)
	{
		AttackComponent->InitiateAttack();
	}
}

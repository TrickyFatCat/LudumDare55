// Made by Titled Goose Team during Ludum Dare 55


#include "AnimNotify_FinishAttack.h"

#include "LudumDare55/Components/CharacterAttackComponent.h"

void UAnimNotify_FinishAttack::Notify(USkeletalMeshComponent* MeshComp,
                                      UAnimSequenceBase* Animation,
                                      const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	UCharacterAttackComponent* AttackComponent = MeshComp->GetOwner()->GetComponentByClass<UCharacterAttackComponent>();

	if (AttackComponent)
	{
		AttackComponent->FinishAttack();
	}
}

// Made by Titled Goose Team during Ludum Dare 55

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterDeathComponent.generated.h"


class AAIController;
class UCharacterMovementComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUDUMDARE55_API UCharacterDeathComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCharacterDeathComponent();

protected:
	virtual void InitializeComponent() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* AnimMontage = nullptr;

public:
	UFUNCTION(BlueprintCallable)
	void StartDeathSequence();
	
private:
	UPROPERTY()
	ACharacter* Character = nullptr;

	UPROPERTY()
	TObjectPtr<AAIController> AIController = nullptr;
};

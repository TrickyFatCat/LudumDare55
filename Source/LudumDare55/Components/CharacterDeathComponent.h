// Made by Titled Goose Team during Ludum Dare 55

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterDeathComponent.generated.h"


class AAIController;
class UCharacterMovementComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSequenceStartedDynamicSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSequenceFinishedDynamicSignature);

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
	UPROPERTY(BlueprintAssignable)
	FOnDeathSequenceStartedDynamicSignature OnDeathSequenceStarted;

	UPROPERTY(BlueprintAssignable)
	FOnDeathSequenceFinishedDynamicSignature OnDeathSequenceFinished;
	
	UFUNCTION(BlueprintCallable)
	void StartDeathSequence();

private:
	UPROPERTY()
	ACharacter* Character = nullptr;

	UPROPERTY()
	TObjectPtr<AAIController> AIController = nullptr;

	UFUNCTION()
	void HandleControllerChanged(APawn* Pawn, AController* OldController, AController* NewController);
};

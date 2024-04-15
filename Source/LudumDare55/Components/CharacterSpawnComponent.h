// Made by Titled Goose Team during Ludum Dare 55

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterSpawnComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSpawnStartedDynamicSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSpawnFinishedDynamicSignature);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUDUMDARE55_API UCharacterSpawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCharacterSpawnComponent();

protected:
	virtual void InitializeComponent() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* AnimMontage = nullptr;

public:
	UPROPERTY(BlueprintAssignable)
	FOnSpawnStartedDynamicSignature OnSpawnStarted;

	UPROPERTY(BlueprintAssignable)
	FOnSpawnFinishedDynamicSignature OnSpawnFinished;
	
	UFUNCTION(BlueprintCallable)
	void StartSpawn();
	
	UFUNCTION(BlueprintCallable)
	void FinishSpawn();
	
private:
	UPROPERTY()
	ACharacter* Character = nullptr;

	UPROPERTY()
	TObjectPtr<AAIController> AIController = nullptr;
};

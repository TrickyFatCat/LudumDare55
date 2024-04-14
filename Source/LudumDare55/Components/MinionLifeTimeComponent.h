// Made by Titled Goose Team during Ludum Dare 55

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MinionLifeTimeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLifeExpiredDyanmicSignature);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUDUMDARE55_API UMinionLifeTimeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMinionLifeTimeComponent();

	UPROPERTY(BlueprintAssignable)
	FOnLifeExpiredDyanmicSignature OnLifeExpired;

	UFUNCTION(BlueprintCallable)
	void StopTimer();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float LifeDuration = 5.f;

	UPROPERTY(BlueprintReadOnly)
	FTimerHandle LifeTimerHandle;

	UFUNCTION()
	void HandleLifeExpired();
};

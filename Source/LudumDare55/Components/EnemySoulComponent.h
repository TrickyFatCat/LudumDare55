// Made by Titled Goose Team during Ludum Dare 55

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemySoulComponent.generated.h"


class USoulsCounterComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUDUMDARE55_API UEnemySoulComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UEnemySoulComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 SoulsAmount = 1;

	UPROPERTY()
	TObjectPtr<USoulsCounterComponent> SoulsCounterComponent = nullptr;

public:
	UFUNCTION(BlueprintCallable)
	void IncreaseSouls();
};

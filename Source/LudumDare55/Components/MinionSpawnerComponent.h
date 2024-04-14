// Made by Titled Goose Team during Ludum Dare 55

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MinionSpawnerComponent.generated.h"

class AMinion;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMinionSpawnedDynamicSignature,
                                             UMinionSpawnerComponent*, Component,
                                             AMinion*, Minion);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUDUMDARE55_API UMinionSpawnerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMinionSpawnerComponent();

	UPROPERTY(BlueprintAssignable)
	FOnMinionSpawnedDynamicSignature OnMinionSpawned;

	UFUNCTION(BlueprintCallable)
	bool SpawnMinion(TSubclassOf<AMinion> MinionClass);
};

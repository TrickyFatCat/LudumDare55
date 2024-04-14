// Made by Titled Goose Team during Ludum Dare 55

#pragma once

#include "CoreMinimal.h"
#include "ScalableFloat.h"
#include "Components/ActorComponent.h"
#include "GraveUpgradeComponent.generated.h"


class USoulsCounterComponent;
class UMinionsCounterComponent;
class AMinion;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnGraveUpgradedDynamicDelegate,
                                              TSubclassOf<AMinion>, Class,
                                              int32, NewLevel,
                                              int32, NewUpgradeCost,
                                              bool, bEnoughSouls);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUDUMDARE55_API UGraveUpgradeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UGraveUpgradeComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AMinion> MinionClass = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat UpgradeTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 UpgradeCost = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 InitialLevel = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Level = 0;

public:
	UPROPERTY(BlueprintAssignable)
	FOnGraveUpgradedDynamicDelegate OnGraveUpgraded;
	
	UFUNCTION(BlueprintCallable)
	bool Upgrade();

private:
	UPROPERTY()
	TObjectPtr<UMinionsCounterComponent> MinionsCounterComponent = nullptr;

	UPROPERTY()
	TObjectPtr<USoulsCounterComponent> SoulsCounterComponent = nullptr;
};

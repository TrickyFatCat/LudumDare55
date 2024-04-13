// Made by Titled Goose Team during Ludum Dare 55

#pragma once

#include "CoreMinimal.h"

#include "SoulsCounterComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnSoulsAddedDynamicSignature,
                                               USoulsCounterComponent*, Component,
                                               int32, NewSouls,
                                               int32, DeltaSouls);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnSoulsSpentDynamicSignature,
                                               USoulsCounterComponent*, Component,
                                               int32, NewSouls,
                                               int32, DeltaSouls);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUDUMDARE55_API USoulsCounterComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	USoulsCounterComponent();

protected:
	virtual void InitializeComponent() override;

public:
	UFUNCTION(BlueprintCallable)
	bool AddSouls(const int32 Amount);

	UFUNCTION(BlueprintCallable)
	bool SpendSouls(const int32 Amount);

	UFUNCTION(BlueprintGetter)
	int32 GetSouls() const { return Souls; }

private:
	UPROPERTY(BlueprintGetter=GetSouls)
	int32 Souls = 0;
};

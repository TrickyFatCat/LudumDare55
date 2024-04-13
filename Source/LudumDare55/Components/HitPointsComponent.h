// Made by Titled Goose Team during Ludum Dare 55

#pragma once

#include "CoreMinimal.h"
#include "Components/SimpleResourceComponent.h"
#include "HitPointsComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUDUMDARE55_API UHitPointsComponent : public USimpleResourceComponent
{
	GENERATED_BODY()

private:
	UHitPointsComponent();

protected:
	virtual void InitializeComponent() override;

	UFUNCTION()
	void HandleAnyDamageTaken(AActor* DamagedActor,
	                          float Damage,
	                          const UDamageType* DamageType,
	                          AController* InstigatedBy, AActor* DamageCauser);
};

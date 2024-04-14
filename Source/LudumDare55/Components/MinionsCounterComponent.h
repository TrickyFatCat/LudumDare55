// Made by Titled Goose Team during Ludum Dare 55

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MinionsCounterComponent.generated.h"

class AMinion;

USTRUCT(BlueprintType)
struct FMinionCounterData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AMinion> MinionClass = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 CurrentNumber = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MaxNumber = 0;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMinionsNumberIncreasedDynamicSignature, FMinionCounterData, Data);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMinionsNumberDecreasedDynamicSignature, FMinionCounterData, Data);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMinionsMaxNumberIncreasedDynamicSignature, FMinionCounterData, Data);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUDUMDARE55_API UMinionsCounterComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMinionsCounterComponent();

protected:
	virtual void InitializeComponent() override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnMinionsNumberIncreasedDynamicSignature OnMinionsNumberIncreased;
	
	UPROPERTY(BlueprintAssignable)
	FOnMinionsNumberDecreasedDynamicSignature OnMinionsNumberDecreased;

	UPROPERTY(BlueprintAssignable)
	FOnMinionsMaxNumberIncreasedDynamicSignature OnMinionsMaxNumberIncreased;
	
	UFUNCTION(BlueprintCallable)
	bool IncrementCounter(TSubclassOf<AMinion> MinionClass);
	
	UFUNCTION(BlueprintCallable)
	bool DecrementCounter(TSubclassOf<AMinion> MinionClass);

	UFUNCTION(BlueprintCallable)
	bool IncreaseMaxNumber(TSubclassOf<AMinion> MinionClass, const int32 Amount);

	UFUNCTION(BlueprintPure)
	bool GetMinionCounterData(TSubclassOf<AMinion> MinionClass, FMinionCounterData& OutData);
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	TArray<FMinionCounterData> MinionCounters;
};

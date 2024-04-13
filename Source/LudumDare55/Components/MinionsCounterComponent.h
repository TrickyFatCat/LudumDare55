// Made by Titled Goose Team during Ludum Dare 55

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MinionsCounterComponent.generated.h"

USTRUCT(BlueprintType)
struct FMinionCounterData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TSubclassOf<AActor> MinionClass = nullptr;
	
	UPROPERTY(BlueprintReadOnly)
	int32 CurrentNumber = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 MaxNumber = 0;

	static bool IncrementCurrentNumber(FMinionCounterData& Data)
	{
		if (Data.CurrentNumber >= Data.MaxNumber)
		{
			return false;
		}
		
		Data.CurrentNumber += 1;
		Data.CurrentNumber = FMath::Min(Data.CurrentNumber, Data.MaxNumber);
		return true;
	}
	
	static bool DecrementCurrentNumber(FMinionCounterData& Data)
	{
		if (Data.CurrentNumber <= 0)
		{
			return false;
		}
		
		Data.CurrentNumber -= 1;
		Data.CurrentNumber = FMath::Max(Data.CurrentNumber, 0);
		return true;
	}
	
	static bool IncreaseMaxNumber(FMinionCounterData& Data, const int32 Amount)
	{
		if (Amount <= 0)
		{
			return false;
		}
		
		Data.MaxNumber += Amount;
		return true;
	}
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
	bool IncrementCounter(TSubclassOf<AActor> MinionClass);
	
	UFUNCTION(BlueprintCallable)
	bool DecrementCounter(TSubclassOf<AActor> MinionClass);

	UFUNCTION(BlueprintCallable)
	bool IncreaseMaxNumber(TSubclassOf<AActor> MinionClass, const int32 Amount);

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess))
	TArray<FMinionCounterData> MinionCounters;

	bool GetMinionCounterData(TSubclassOf<AActor> MinionClass, FMinionCounterData& OutMinionCounterData);
};

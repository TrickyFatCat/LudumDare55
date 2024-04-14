// Made by Titled Goose Team during Ludum Dare 55


#include "MinionsCounterComponent.h"

#include "LudumDare55/Characters/Minion.h"


UMinionsCounterComponent::UMinionsCounterComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UMinionsCounterComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

bool UMinionsCounterComponent::IncrementCounter(TSubclassOf<AMinion> MinionClass)
{
	FMinionCounterData MinionCounterData;

	if (!GetMinionCounterData(MinionClass, MinionCounterData))
	{
		return false;
	}

	if (!FMinionCounterData::IncrementCurrentNumber(MinionCounterData))
	{
		return false;
	}

	OnMinionsNumberIncreased.Broadcast(MinionCounterData);
	return true;
}

bool UMinionsCounterComponent::DecrementCounter(TSubclassOf<AMinion> MinionClass)
{
	FMinionCounterData MinionCounterData;

	if (!GetMinionCounterData(MinionClass, MinionCounterData))
	{
		return false;
	}

	if (!FMinionCounterData::DecrementCurrentNumber(MinionCounterData))
	
	{
		return false;
	}

	OnMinionsNumberDecreased.Broadcast(MinionCounterData);
	return true;
}

bool UMinionsCounterComponent::IncreaseMaxNumber(TSubclassOf<AMinion> MinionClass, const int32 Amount)
{
	FMinionCounterData MinionCounterData;

	if (!GetMinionCounterData(MinionClass, MinionCounterData))
	{
		return false;
	}

	if (!FMinionCounterData::IncreaseMaxNumber(MinionCounterData, Amount))
	{
		return false;
	}

	OnMinionsMaxNumberIncreased.Broadcast(MinionCounterData);
	return true;
}

bool UMinionsCounterComponent::GetMinionCounterData(TSubclassOf<AMinion> MinionClass,
                                                    FMinionCounterData& OutMinionCounterData)
{
	if (!MinionClass || MinionCounters.IsEmpty())
	{
		return false;
	}

	auto Predicate = [&](const FMinionCounterData& Data)
	{
		return Data.MinionClass == MinionClass;
	};

	if (!MinionCounters.ContainsByPredicate(Predicate))
	{
		return false;
	}

	OutMinionCounterData = *MinionCounters.FindByPredicate(Predicate);
	return true;
}
